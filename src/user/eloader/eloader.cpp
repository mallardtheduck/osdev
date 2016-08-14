#include <btos.h>
#include "util.hpp"

char stdout_path[BT_MAX_PATH];
bt_handle_t stdout;

char program_arg[BT_MAX_PATH];
char program_path[BT_MAX_PATH];
bt_handle_t program_file;


void puts(const char *str){
	bt_fwrite(stdout, strlen(str), str);
}

int main(){
	bt_getenv("STDOUT", stdout_path, BT_MAX_PATH);
	stdout=bt_fopen(stdout_path, FS_Write);
	
	size_t argc = bt_get_argc();
	if(argc < 2) return -1;
	bt_get_arg(1, program_arg, BT_MAX_PATH);
	btos_path_parse(program_arg, program_path, BT_MAX_PATH);
	puts(program_path);
	puts("\n");
	
	program_file = bt_fopen(program_path, FS_Read);
	Elf32_Ehdr ehdr = elf_read_header(program_file);
	
	
    return 0;
}

extern "C" void _start(){
	int ret=main();
	bt_exit(ret);
}