#include "ps2.hpp"

#pragma GCC diagnostic ignored "-Wunused-parameter"

const uint16_t PS2_Data_Port     =0x60;
const uint16_t PS2_Status_Port   =0x64;
const uint16_t PS2_Command_Port  =0x64;

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

void init_keyboard();

extern "C" int module_main(syscall_table *systbl, char *params) {
    SYSCALL_TABLE = systbl;
    init_keyboard();
    return 0;
}

uint8_t ps2_read_data(){
    return inb(PS2_Data_Port);
}

uint8_t ps2_read_status(){
    return inb(PS2_Status_Port);
}

void ps2_write_command(uint8_t byte){
    outb(PS2_Command_Port, byte);
}