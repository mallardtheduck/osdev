#include "ps2.hpp"
#include <util/circular_buffer.hpp>

#pragma GCC diagnostic ignored "-Wunused-parameter"

static bool input_available=false;
static constexpr bt_mouse_packet zero_packet={0, 0, 0};

static circular_buffer<bt_mouse_packet, 512> mouse_buffer{zero_packet};
static circular_buffer<uint8_t, 48> pre_buffer{0};

static uint8_t irq;
static uint64_t mouse_thread_id;
static ILock *buf_lock;

static btos_api::hwpnp::IPS2Bus *theBus;
static size_t theIndex;

static void mouse_handler(ICPUState &){
	uint8_t ps2_byte = theBus->ReadDataWithoutStatusCheck();
	pre_buffer.add_item(ps2_byte);
	input_available = true;
	/*if(thread_id()!=mouse_thread_id) {
		enable_interrupts();
		yield();
		disable_interrupts();
	}*/
}

void mouse_thread(){
	auto &currentThread = API->CurrentThread();
	currentThread.SetName("Mouse");
	currentThread.SetPriority(1);
	while(true){
		uint8_t byte1=0, byte2=0, byte3=0;
		while(!(byte1 & (1 << 3))) {
			currentThread.SetBlock([]{
					return !!pre_buffer.count();
				});
			disable_interrupts();
			byte1 = pre_buffer.read_item();
			input_available = false;
			enable_interrupts();
		}
		currentThread.SetBlock([]{
				return !!pre_buffer.count();
			});
		disable_interrupts();
		byte2=pre_buffer.read_item();
		input_available=false;
		enable_interrupts();
		currentThread.SetBlock([]{
				return !!pre_buffer.count();
			});
		disable_interrupts();
		byte3=pre_buffer.read_item();
		input_available=false;
		enable_interrupts();

		uint8_t state=byte1;
		int16_t mouse_x=byte2 - ((state << 4) & 0x100);
		int16_t mouse_y=byte3 - ((state << 3) & 0x100);

		if(!(state & (1 << 3))){
			dbgpf("PS2: Invalid first mouse byte: %x!\n", state);
			disable_interrupts();
			pre_buffer.clear();
			input_available=false;
			enable_interrupts();
			API->GetHAL().DisableIRQ(irq);
			theBus->WritePort(theIndex, Device_Command::Reset);
			theBus->WritePort(theIndex, Device_Command::EnableReporting);
			API->GetHAL().EnableIRQ(irq);
			continue;
		}

		bool button1=state & (1 << 0);
		bool button2=state & (1 << 1);
		bool button3=state & (1 << 2);
		bt_mouse_packet packet;
		packet.flags = MouseFlags::Valid | (button1?MouseFlags::Button1:0) | (button2?MouseFlags::Button2:0) | (button3?MouseFlags::Button3:0);
		packet.x_motion=mouse_x;
		packet.y_motion=mouse_y;
		buf_lock->TakeExclusive();
		mouse_buffer.add_item(packet);
		buf_lock->Release();
	}
}

size_t mouse_read(btos_api::hwpnp::IPS2Bus *bus, size_t index, size_t bytes, char *cbuf){
	if((bytes % sizeof(bt_mouse_packet))) return 0;
	size_t values = bytes / sizeof(bt_mouse_packet);
	bt_mouse_packet *buf=(bt_mouse_packet*)cbuf;
	if(values > mouse_buffer.max_size()) values=mouse_buffer.max_size();
	while(true){
		if(mouse_buffer.count() < values){
			API->CurrentThread().SetBlock([&]{
				return mouse_buffer.count() >= values;
			});
		}
		buf_lock->TakeExclusive();
		if(mouse_buffer.count() >= values) break;
		buf_lock->Release();
	}
	for(size_t i=0; i<values; ++i){
		bt_mouse_packet buffervalue=mouse_buffer.read_item();
		buf[i]=buffervalue;
	}
	buf_lock->Release();
	return bytes;
}

void init_mouse(btos_api::hwpnp::IPS2Bus *bus, size_t index){
	auto busLock = bus->GetLock();
	buf_lock = API->NewLock();
	irq = bus->GetIRQ(index);
	bus->EnableDevice(index);
	
	bus->WritePort(index, Device_Command::Identify);
	uint8_t id=ps2_read_data();
	dbgpf("PS: Mouse type: %x\n", (int)id);
	bus->WritePort(index, Device_Command::Reset);
	bus->WritePort(index, Device_Command::DisableReporting);

	pre_buffer.clear();
	API->GetHAL().HandleIRQ(irq, &mouse_handler);
	mouse_thread_id = API->GetScheduler().NewThread(&mouse_thread);
	bus->WritePort(index, Device_Command::EnableReporting);
	API->GetHAL().EnableIRQ(irq);
}

PS2MouseDevice::PS2MouseDevice(btos_api::hwpnp::IPS2Bus *b, size_t i) : bus(b), index(i), node(this) {
	theBus = bus;
	theIndex = index;
	init_mouse(bus, index);
}

btos_api::hwpnp::DeviceID PS2MouseDevice::GetID(){
	return PS2KeyboardDeviceID;
}

const char *PS2MouseDevice::GetDescription(){
	return "PS/2 mouse";
}

size_t PS2MouseDevice::GetSubDeviceCount(){
	return 0;
}

btos_api::hwpnp::DeviceID PS2MouseDevice::GetSubDevice(size_t){
	return btos_api::hwpnp::NullDeviceID;
}

btos_api::hwpnp::IDriver *PS2MouseDevice::GetDriver(){
	return GetPS2MouseDriver();
}

btos_api::hwpnp::IDeviceNode *PS2MouseDevice::GetDeviceNode(){
	return &node;
}
	
size_t PS2MouseDevice::Read(size_t bytes, char *buf){
	return mouse_read(bus, index, bytes, buf);
}

void PS2MouseDevice::ClearBuffer(){
	buf_lock->TakeExclusive();
	mouse_buffer.clear();
	buf_lock->Release();
}

PS2MouseDeviceNode::PS2MouseDeviceNode(btos_api::hwpnp::IMouse *d) : btos_api::hwpnp::MouseDeviceNode(d) {}

const char *PS2MouseDeviceNode::GetBaseName(){
	return "MOUSE";
}
