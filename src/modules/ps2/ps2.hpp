#ifndef _PS2_HPP
#define _PS2_HPP

#include "module_stubs.h"
#include "module_cpp.hpp"
#include "keyboard.h"
#include "mouse.h"
#include "io.h"

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

#endif