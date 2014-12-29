#include "ps2.hpp"

#pragma GCC diagnostic ignored "-Wunused-parameter"

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

extern "C" int module_main(syscall_table *systbl, char *params) {
    SYSCALL_TABLE = systbl;
    dbgout("PS2: Disable ports\n");
    ps2_write_command(PS2_Command::DisablePort1);
    ps2_write_command(PS2_Command::DisablePort2);
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
    dbgout("PS2: Controller self-test\n");
    ps2_write_command(PS2_Command::TestController);
    uint8_t test=ps2_read_data();
    if(test != 0x55){
        dbgout("PS2: contoller failed self-test!\n");
        return 0;
    }
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
    uint8_t keyport=0, mouseport=0;
    ps2_clear_data();
    if(ch1){
        ps2_write_command(PS2_Command::EnablePort1);
        ps2_write_command(PS2_Command::DisablePort2);
        ps2_write_port1(Device_Command::Reset);
        if(uint8_t p0test = ps2_read_data() != 0xAA){
            dbgpf("PS2: Device 1 self-test result: %x\n", (int)p0test);
            dbgout("PS2: Device 1 failed self-test!\n");
            ch1=false;
        }else {
            ps2_write_port1(Device_Command::Identify);
            ps2_read_data();
            uint8_t id = ps2_read_data();
            dbgpf("PS2: Detected device id: %x on port 1.\n", (int)id);
            if (id == Device_Types::MF2Keyboard || id == Device_Types::ATKeyboard) keyport = 1;
            else mouseport = 1;
        }
        ps2_write_command(PS2_Command::DisablePort1);
    }
    if(ch2){
        ps2_write_command(PS2_Command::EnablePort2);
        ps2_write_command(PS2_Command::DisablePort1);
        ps2_write_port2(Device_Command::Reset);
        if(ps2_read_data() != 0xAA){
            dbgout("PS2: Device 2 failed self-test!\n");
            ch2=false;
        }else {
            ps2_write_port2(Device_Command::Identify);
            ps2_read_data();
            uint8_t id = ps2_read_data();
            dbgpf("PS2: Detected device id: %x on port 2.\n", (int)id);
            if (id == Device_Types::MF2Keyboard || id == Device_Types::ATKeyboard) keyport = 2;
            else mouseport = 2;
        }
        ps2_write_command(PS2_Command::DisablePort2);
    }
    dbgpf("PS2: Ports: Keyboard: %i, Mouse: %i\n", (int)keyport, (int)mouseport);
    if(keyport) init_keyboard(1);
    //panic("(PS2) TEST");
    return 0;
}

uint8_t ps2_read_data(){
    while(!(ps2_read_status() & 1));
    return inb(PS2_Data_Port);
}

void ps2_write_data(uint8_t byte){
    while(ps2_read_status() & (1 << 1));
    outb(PS2_Data_Port, byte);
}

uint8_t ps2_read_status(){
    return inb(PS2_Status_Port);
}

void ps2_write_command(uint8_t byte){
    outb(PS2_Command_Port, byte);
}

void ps2_write_port1(uint8_t byte){
    ps2_write_data(byte);
}

void ps2_write_port2(uint8_t byte){
    ps2_write_command(PS2_Command::WritePort2InBuffer);
    ps2_write_data(byte);
}

void ps2_clear_data(){
    while(ps2_read_status() & 1) inb(PS2_Data_Port);
}