#ifndef _PS2_HPP
#define _PS2_HPP

#include <btos_module.h>
#include <dev/keyboard.h>
#include <dev/mouse.h>
#include <dev/hwpnp/ps2bus.hpp>
#include <dev/hwpnp/keyboard.hpp>
#include <dev/hwpnp/mouse.hpp>
#include <util/ministl.hpp>

static const btos_api::hwpnp::DeviceID PCPS2DeviceID = {
		btos_api::hwpnp::PNPBUS::PCBUS,
		0, 0, 0, 0, 3
};

static const btos_api::hwpnp::DeviceID PS2KeyboardDeviceID = {
	btos_api::hwpnp::PNPBUS::PS2,
	0, 0, 0, 0, btos_api::hwpnp::PS2DeviceClass::Keyboard
};

static const btos_api::hwpnp::DeviceID PS2MouseDeviceID = {
	btos_api::hwpnp::PNPBUS::PS2,
	0, 0, 0, 0, btos_api::hwpnp::PS2DeviceClass::Mouse
};

uint8_t ps2_read_data();
uint8_t ps2_read_data_nocheck();
void ps2_write_data(uint8_t byte);
uint8_t ps2_read_status();
void ps2_write_command(uint8_t byte);
void ps2_write_port1(uint8_t byte);
void ps2_write_port2(uint8_t byte);
void ps2_clear_data();

void init_keyboard(uint8_t channel);
void init_mouse(uint8_t channel);

const uint16_t PS2_Data_Port     =0x60;
const uint16_t PS2_Status_Port   =0x64;
const uint16_t PS2_Command_Port  =0x64;

const uint8_t Port1IRQ = 1;
const uint8_t Port2IRQ =12;

namespace PS2_Command{
    enum{
        ReadRAM             =0x20,
        WriteRAM            =0x60,
        DisablePort2        =0xA7,
        EnablePort2         =0xA8,
        TestPort2           =0xA9,
        TestController      =0xAA,
        TestPort1           =0xAB,
        DisablePort1        =0xAD,
        EnablePort1         =0xAE,
        ReadOutput          =0xD0,
        WriteOutput         =0xD1,
        WritePort1OutBuffer =0xD2,
        WritePort2OutBuffer =0xD3,
        WritePort2InBuffer  =0xD4,
        ResetCPU            =0xFE,

    };
};

namespace Device_Command{
    enum{
    // Keyboard commands
        SetLEDs             =0xED,
        Echo                =0xEE,
        GetSetScanCode      =0xF0,
        SetTypematicRate    =0xF3,
        EnableScanning      =0xF4,
        DisableScanning     =0xF5,
        SetDefaults         =0xF6,
        SetTypematicOnly    =0xF7,
        SetMakeReleaseOnly  =0xF8,
        SetMakeOnly         =0xF9,
        SetAll              =0xFA,
        SetKeyTMOnly        =0xFB,
        SetKeyMROnly        =0xFC,
        SetKeyMakeOnly      =0xFD,

    // Mouse commands
        StatusRequest       =0xE9,
        SetStreamMode       =0xEA,
        ReadData            =0xEB,
        ResetWrapMode       =0xEC,
        SetWrapMode         =0xEE,
        SetRemoteMode       =0xF0,
        SetSampleRate       =0xF3,
        EnableReporting     =0xF4,
        DisableReporting    =0xF5,

    // Common commands
        Identify            =0xF2,
        ResendByte          =0xFE,
        Reset               =0xFF,
    };
}

namespace Device_Types{
    enum{
        ATKeyboard          =0xAA,
        StdMouse            =0x00,
        ScrollMouse         =0x03,
        FiveBtnMouse        =0x04,
        MF2Keyboard         =0xAB,
    };
}

btos_api::hwpnp::IDriver *GetPS2Driver();
btos_api::hwpnp::IDriver *GetPS2KeyboardDriver();
btos_api::hwpnp::IDriver *GetPS2MouseDriver();

class PS2BusDevice : public btos_api::hwpnp::IPS2Bus{
private:
	map<size_t, btos_api::hwpnp::DeviceID> devices;
protected:
	void Lock();
	void Unlock();
public:
	void SetDevice(size_t index, btos_api::hwpnp::DeviceID);

	PS2BusDevice();

	btos_api::hwpnp::DeviceID GetID();
	const char *GetDescription();
	size_t GetSubDeviceCount();
	btos_api::hwpnp::DeviceID GetSubDevice(size_t);
	btos_api::hwpnp::IDriver *GetDriver();
	
	uint8_t ReadData();
	uint8_t ReadDataWithoutStatusCheck();
	void WriteData(uint8_t byte);
	void ClearData();
	uint8_t ReadStatus();
	void WriteCommand(uint8_t byte);
	void WritePort(size_t index, uint8_t byte);
	uint8_t GetIRQ(size_t index);
	void EnableDevice(size_t index);
};

class PS2KeyboardDeviceNode : public btos_api::hwpnp::KeyboardDeviceNode{
public:
	PS2KeyboardDeviceNode(btos_api::hwpnp::IKeyboard *d);
	const char *GetBaseName();
};

class PS2KeyboardDevice : public btos_api::hwpnp::IKeyboard{
private:
	btos_api::hwpnp::IPS2Bus *bus;
	size_t index;
	PS2KeyboardDeviceNode node;
public:
	PS2KeyboardDevice(btos_api::hwpnp::IPS2Bus *bus, size_t index);

	btos_api::hwpnp::DeviceID GetID();
	const char *GetDescription();
	size_t GetSubDeviceCount();
	btos_api::hwpnp::DeviceID GetSubDevice(size_t);
	btos_api::hwpnp::IDriver *GetDriver();
	btos_api::hwpnp::IDeviceNode *GetDeviceNode();
	
	size_t Read(size_t bytes, char *buf);
};

class PS2MouseDeviceNode : public btos_api::hwpnp::MouseDeviceNode{
public:
	PS2MouseDeviceNode(btos_api::hwpnp::IMouse *d);
	const char *GetBaseName();
};

class PS2MouseDevice : public btos_api::hwpnp::IMouse{
private:
	btos_api::hwpnp::IPS2Bus *bus;
	size_t index;
	PS2MouseDeviceNode node;
public:
	PS2MouseDevice(btos_api::hwpnp::IPS2Bus *bus, size_t index);

	btos_api::hwpnp::DeviceID GetID();
	const char *GetDescription();
	size_t GetSubDeviceCount();
	btos_api::hwpnp::DeviceID GetSubDevice(size_t);
	btos_api::hwpnp::IDriver *GetDriver();
	btos_api::hwpnp::IDeviceNode *GetDeviceNode();
	
	size_t Read(size_t bytes, char *buf);
	void ClearBuffer();
};

#endif