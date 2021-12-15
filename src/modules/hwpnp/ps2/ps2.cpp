#include "ps2.hpp"
#include <module/module.inc>

#pragma GCC diagnostic ignored "-Wunused-parameter"

char dbgbuf[256];

ILock *ps2_lock;

int module_main(char *) {
	auto &hwPnp = API->GetHwPnPManager();
	hwPnp.RegisterDriver(GetPS2Driver());
	hwPnp.RegisterDriver(GetPS2KeyboardDriver());
	hwPnp.RegisterDriver(GetPS2MouseDriver());
	return 0;
}
	
void ps2_init(PS2BusDevice *dev){
	ps2_lock = API->NewLock();
	dbgout("PS2: Disable ports\n");
	ps2_write_command(PS2_Command::DisablePort1);
	ps2_write_command(PS2_Command::DisablePort2);
	ps2_clear_data();
	dbgout("PS2: Read config\n");
	ps2_write_command(PS2_Command::ReadRAM);
	uint8_t config=ps2_read_data();
	dbgpf("PS2: Config: %x\n", (int)config);
	bool ch2=config & (1 << 5);
	config=config | (1 << 0) | (1 << 1);
	config=config & ~(1 << 6);
	dbgout("PS2: Write config\n");
	ps2_write_command(PS2_Command::WriteRAM);
	ps2_write_data(config);
	/*dbgout("PS2: Controller self-test\n");
	ps2_write_command(PS2_Command::TestController);
	uint8_t test=ps2_read_data();
	if(test != 0x55){
		dbgout("PS2: contoller failed self-test!\n");
		return 0;
	}*/
	if(ch2){
		ps2_write_command(PS2_Command::EnablePort2);
		ps2_write_command(PS2_Command::ReadRAM);
		config=ps2_read_data();
		if(config & (1 << 5)) ch2=false;
		else ps2_write_command(PS2_Command::DisablePort2);
	}
	ps2_write_command(PS2_Command::TestPort1);
	bool ch1=!ps2_read_data();
	if(ch2) {
		ps2_write_command(PS2_Command::TestPort2);
		ch2=!ps2_read_data();
	}
	ps2_clear_data();
	if(ch1){
		ps2_write_command(PS2_Command::EnablePort1);
		//ps2_write_command(PS2_Command::DisablePort2);
		ps2_clear_data();
		ps2_write_port1(Device_Command::Reset);
		if(uint8_t p1test = ps2_read_data() != 0xAA){
			dbgpf("PS2: Device 1 self-test result: %x\n", (int)p1test);
			dbgout("PS2: Device 1 failed self-test!\n");
			ch1=false;
		}else {
			ps2_write_port1(Device_Command::Identify);
			uint8_t id = ps2_read_data();
			dbgpf("PS2: Detected device id: %x on port 1.\n", (int)id);
			if (id == Device_Types::MF2Keyboard || id == Device_Types::ATKeyboard) dev->SetDevice(0, PS2KeyboardDeviceID);
			else dev->SetDevice(0, PS2MouseDeviceID);
		}
		ps2_write_command(PS2_Command::DisablePort1);
	}
	if(ch2){
		ps2_write_command(PS2_Command::EnablePort2);
		//ps2_write_command(PS2_Command::DisablePort1);
		ps2_clear_data();
		ps2_write_port2(Device_Command::Reset);
		if(uint8_t p2test = ps2_read_data() != 0xAA){
			dbgpf("PS2: Device 2 self-test result: %x\n", (int)p2test);
			dbgout("PS2: Device 2 failed self-test!\n");
			ch2=false;
		}else {
			ps2_write_port2(Device_Command::Identify);
			uint8_t id = ps2_read_data();
			dbgpf("PS2: Detected device id: %x on port 2.\n", (int)id);
			if (id == Device_Types::MF2Keyboard || id == Device_Types::ATKeyboard) dev->SetDevice(1, PS2KeyboardDeviceID);
			else dev->SetDevice(1, PS2MouseDeviceID);
		}
		ps2_write_command(PS2_Command::DisablePort2);
	}
}

uint8_t ps2_read_data(){
	while(!(ps2_read_status() & 1));
	uint8_t ret = inb(PS2_Data_Port);
	return ret;
}

uint8_t ps2_read_data_nocheck(){
	return inb(PS2_Data_Port);
}

void ps2_write_data(uint8_t byte){
	while(ps2_read_status() & (1 << 1));
	outb(PS2_Data_Port, byte);
}

uint8_t ps2_read_status(){
	uint8_t ret = inb(PS2_Status_Port);
	return ret;
}

void ps2_write_command(uint8_t byte){
	while(ps2_read_status() & (1 << 1));
	outb(PS2_Command_Port, byte);
	while(ps2_read_status() & (1 << 1));
}

void ps2_write_port1(uint8_t byte){
	uint8_t result=0xFE;
	while(result != 0xFA) {
		ps2_write_data(byte);
		result=ps2_read_data();
	}
}

void ps2_write_port2(uint8_t byte){
	uint8_t result=0xFE;
	while(result != 0xFA){
		ps2_write_command(PS2_Command::WritePort2InBuffer);
		ps2_write_data(byte);
		result=ps2_read_data();
	}
}

void ps2_clear_data(){
	while(ps2_read_status() & 1) inb(PS2_Data_Port);
}

PS2BusDevice::PS2BusDevice(){
	ps2_init(this);
}

void PS2BusDevice::SetDevice(size_t index, btos_api::hwpnp::DeviceID id){
	devices[index] = id;
}

btos_api::hwpnp::DeviceID PS2BusDevice::GetID(){
	return PCPS2DeviceID;
}

const char *PS2BusDevice::GetDescription(){
	return "8042-style PS/2 input device bus";
}

size_t PS2BusDevice::GetSubDeviceCount(){
	return 2;
}

btos_api::hwpnp::DeviceID PS2BusDevice::GetSubDevice(size_t i){
	if(devices.has_key(i)) return devices[i];
	else return btos_api::hwpnp::NullDeviceID;
}

btos_api::hwpnp::IDriver *PS2BusDevice::GetDriver(){
	return GetPS2Driver();
}

uint8_t PS2BusDevice::ReadData(){
	return ps2_read_data();
}

uint8_t PS2BusDevice::ReadDataWithoutStatusCheck(){
	return ps2_read_data_nocheck();
}

void PS2BusDevice::WriteData(uint8_t byte){
	ps2_write_data(byte);
}

void PS2BusDevice::ClearData(){
	ps2_clear_data();
}

uint8_t PS2BusDevice::ReadStatus(){
	return ps2_read_status();
}

void PS2BusDevice::WriteCommand(uint8_t byte){
	ps2_write_command(byte);
}

void PS2BusDevice::WritePort(size_t index, uint8_t byte){
	if(index == 0) ps2_write_port1(byte);
	else if(index == 1) ps2_write_port2(byte);
}

uint8_t PS2BusDevice::GetIRQ(size_t index){
	if(index == 0) return Port1IRQ;
	else if(index == 1) return Port2IRQ;
	return 0;
}

void PS2BusDevice::EnableDevice(size_t index){
	if(index == 0) ps2_write_command(PS2_Command::EnablePort1);
	else if(index == 1) ps2_write_command(PS2_Command::EnablePort2);
}

void PS2BusDevice::Lock(){
	ps2_lock->TakeExclusive();
}


void PS2BusDevice::Unlock(){
	ps2_lock->Release();
}