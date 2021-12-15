#include "ps2.hpp"
#include <util/circular_buffer.hpp>

#pragma GCC diagnostic ignored "-Wunused-parameter"

static circular_buffer<uint32_t, 128> keyboard_buffer;
static ILock *buf_lock;
static bool input_available;
static uint16_t currentflags=0;
static uint8_t irq;
static uint64_t keyboard_thread_id;

static circular_buffer<uint8_t, 16> pre_buffer;

static key_info *layout;
static uint8_t *capskeys;
static uint8_t *numkeys;

extern key_info us_keyboard_layout[128];
extern uint8_t us_keyboard_capskeys[];
extern uint8_t us_keyboard_numkeys[];

static void updateflags(uint16_t keycode);
static uint16_t scancode2keycode(uint8_t c);
static uint32_t scancode2buffervalue(uint8_t c);

static btos_api::hwpnp::IPS2Bus *theBus;
static size_t theIndex;

static void keyboard_handler(ICPUState &){
	uint8_t ps2_byte=theBus->ReadDataWithoutStatusCheck();
	if(ps2_byte == 0xFA) return;
	pre_buffer.add_item(ps2_byte);
	input_available = true;
}

static void keyboard_thread(){
	auto &currentThread = API->CurrentThread();
	currentThread.SetPriority(1);
	while(true){
		currentThread.SetBlock([]{
			return input_available;
		});
		auto hl = buf_lock->LockExclusive();
		disable_interrupts();
		while(uint8_t key=pre_buffer.read_item()) {
			if (!keyboard_buffer.full()) {
				uint16_t keycode = scancode2keycode(key);
				if (keycode) {
					keyboard_buffer.add_item(scancode2buffervalue(key));
					updateflags(keycode);
				} else {
					dbgpf("PS2: KEYBOARD: Ignored unmapped scancode %x (%x).\n", (int) key, (int) keycode);
				}
			}
		}
		input_available = false;
		enable_interrupts();
	}
}

static bool is_capskey(uint8_t c){
	uint8_t *ptr=capskeys;
	while(true){
		if(!ptr || !*ptr) return false;
		if(*ptr==c) return true;
		ptr++;
	}
}

static bool is_numkey(uint8_t c){
	uint8_t *ptr=numkeys;
	while(true){
		if(!ptr || !*ptr) return false;
		if(*ptr==c) return true;
		ptr++;
	}
}

static uint16_t scancode2keycode(uint8_t c){
	uint16_t ret=0;
	if(c & 0x80){
		ret |= KeyFlags::KeyUp;
		c &= ~0x80;
	}
	size_t index=KI_Normal;
	if(currentflags & KeyFlags::Shift) index=KI_Shift;
	if(currentflags & KeyFlags::Alt) index=KI_AltGr;
	if(currentflags & KeyFlags::CapsLock && is_capskey(c)){
		if(currentflags & KeyFlags::Shift) index=KI_Normal;
		else index=KI_Shift;
	}
	if(currentflags & KeyFlags::NumLock && is_numkey(c)){
		if(currentflags & KeyFlags::Shift) index=KI_Normal;
		else index=KI_Shift;
    }
	uint16_t code=layout[(size_t)c][index];
	if(code==0) code=layout[(size_t)c][KI_Normal];
	if(code==0) return 0;
	ret |= code | currentflags;
	return ret;
}

static uint32_t scancode2buffervalue(uint8_t c){
	uint8_t flag=Keyboard_Flag;
	uint8_t scancode=c;
	uint16_t keycode=scancode2keycode(c);
	return (flag << 24) | (scancode << 16) | keycode;
}

static void updateflags(uint16_t keycode){
	if(!(keycode & KeyFlags::NonASCII)) return;
	if(keycode & KeyFlags::KeyUp){
		if((keycode & KC_Mask) == KeyCodes::Shift) currentflags &= ~KeyFlags::Shift;
		if((keycode & KC_Mask) == KeyCodes::Alt) currentflags &= ~KeyFlags::Alt;
		if((keycode & KC_Mask) == KeyCodes::Control) currentflags &= ~KeyFlags::Control;
		if((keycode & KC_Mask) == KeyCodes::Meta) currentflags &= ~KeyFlags::Meta;
	} else {
		if((keycode & KC_Mask) == KeyCodes::Shift) currentflags |= KeyFlags::Shift;
		if((keycode & KC_Mask) == KeyCodes::Alt) currentflags |= KeyFlags::Alt;
		if((keycode & KC_Mask) == KeyCodes::Control) currentflags |= KeyFlags::Control;
		if((keycode & KC_Mask) == KeyCodes::Meta) currentflags |= KeyFlags::Meta;
		if((keycode & KC_Mask) == KeyCodes::CapsLock) currentflags ^= KeyFlags::CapsLock;
		if((keycode & KC_Mask) == KeyCodes::NumLock) currentflags ^= KeyFlags::NumLock;
	}
	uint8_t leds=0;
	if(currentflags & KeyFlags::ScrollLock){
		leds |= 1 << 0;
	}
	if(currentflags & KeyFlags::NumLock){
		leds |= 1 << 1;
	}
	if(currentflags & KeyFlags::CapsLock){
		leds |= 1 << 2;
	}
	theBus->WritePort(theIndex, Device_Command::SetLEDs);
	theBus->WriteData(leds);
	return;
}

bool keyread_lockcheck(void *p){
	return keyboard_buffer.count() >= *(size_t*)p;
}

size_t keyboard_read(btos_api::hwpnp::IPS2Bus *bus, size_t index, size_t bytes, char *cbuf){
	if((bytes % sizeof(uint32_t))) return 0;
	size_t values = bytes / sizeof(uint32_t);
	uint32_t *buf=(uint32_t*)cbuf;
	if(values > keyboard_buffer.max_size()) values=keyboard_buffer.max_size();
	while(true){
		if(keyboard_buffer.count() < values){
			API->CurrentThread().SetBlock([&]{
				return keyboard_buffer.count() >= values;
			});
		}
		{
			auto hl = buf_lock->LockExclusive();
			if(keyboard_buffer.count() >= values) break;
		}
	}
	for(size_t i=0; i<values; ++i){
		uint32_t buffervalue=keyboard_buffer.read_item();
		buf[i]=buffervalue;
	}
	return bytes;
}

void init_keyboard(btos_api::hwpnp::IPS2Bus *bus, size_t index){
	auto busLock = bus->GetLock();
	buf_lock = API->NewLock();
	layout=us_keyboard_layout;
	capskeys=us_keyboard_capskeys;
	numkeys=us_keyboard_numkeys;
	input_available=false;
	irq = bus->GetIRQ(index);
	bus->EnableDevice(index);
	bus->WritePort(index, Device_Command::Reset);
	bus->WritePort(index, Device_Command::SetDefaults);
	bus->WritePort(index, Device_Command::DisableScanning);
	bus->WritePort(index, Device_Command::GetSetScanCode);
	bus->WriteData(0x01);
	bus->WritePort(index, Device_Command::GetSetScanCode);
	bus->WriteData(0x00);
	uint8_t byte = 0xFA;
	while(byte == 0xFA) byte = bus->ReadData();
	dbgpf("PS2: Scan set: %x\n", byte);
	if(byte == 0x02 || byte == 0x41){
		if(irq == Port1IRQ){
			dbgpf("PS2: Keyboard does not support scan set 1. Re-enabling translation.\n");
			dbgout("PS2: Read config\n");
			bus->WriteCommand(PS2_Command::ReadRAM);
			uint8_t config=bus->ReadData();
			dbgpf("PS2: Config: %x\n", (int)config);
			config |= (1 << 6);
			dbgout("PS2: Write config\n");
			bus->WriteCommand(PS2_Command::WriteRAM);
			bus->WriteData(config);
		}else{
			panic("(PS2) Keyboard does not support scan set 1 and cannot be translated.");
		}
	}
	bus->WritePort(index, Device_Command::EnableScanning);
	API->GetHAL().HandleIRQ(irq, &keyboard_handler);
	keyboard_thread_id = API->GetScheduler().NewThread(&keyboard_thread)->ID();
	API->GetHAL().EnableIRQ(irq);
	bus->ClearData();
}

PS2KeyboardDevice::PS2KeyboardDevice(btos_api::hwpnp::IPS2Bus *b, size_t i) : bus(b), index(i), node(this) {
	theBus = bus;
	theIndex = index;
	init_keyboard(bus, index);
}

btos_api::hwpnp::DeviceID PS2KeyboardDevice::GetID(){
	return PS2KeyboardDeviceID;
}

const char *PS2KeyboardDevice::GetDescription(){
	return "PS/2 keyboard";
}

size_t PS2KeyboardDevice::GetSubDeviceCount(){
	return 0;
}

btos_api::hwpnp::DeviceID PS2KeyboardDevice::GetSubDevice(size_t){
	return btos_api::hwpnp::NullDeviceID;
}

btos_api::hwpnp::IDriver *PS2KeyboardDevice::GetDriver(){
	return GetPS2KeyboardDriver();
}

btos_api::hwpnp::IDeviceNode *PS2KeyboardDevice::GetDeviceNode(){
	return &node;
}
	
size_t PS2KeyboardDevice::Read(size_t bytes, char *buf){
	return keyboard_read(bus, index, bytes, buf);
}

PS2KeyboardDeviceNode::PS2KeyboardDeviceNode(btos_api::hwpnp::IKeyboard *d) : btos_api::hwpnp::KeyboardDeviceNode(d) {}

const char *PS2KeyboardDeviceNode::GetBaseName(){
	return "KEYBD";
}
