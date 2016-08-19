#include <btos.h>
#include "util.hpp"
#include "elf.hpp"
#include "el_load_elf.hpp"

char stdout_path[BT_MAX_PATH];
bt_handle_t stdout;

char program_arg[BT_MAX_PATH];
char program_path[BT_MAX_PATH];
bt_handle_t program_file;

size_t loader_heap_base = 0xE0000000;

void puts(const char *str){
	bt_fwrite(stdout, strlen(str), str);
}

int main(){
	bt_getenv("STDOUT", stdout_path, BT_MAX_PATH);
	stdout=bt_fopen(stdout_path, FS_Write);
	
	size_t argc = bt_get_argc();
	if(argc < 1) return -1;
	bt_get_arg(0, program_arg, BT_MAX_PATH);
	btos_path_parse(program_arg, program_path, BT_MAX_PATH);
	
	program_file = bt_fopen(program_path, FS_Read);
	entrypoint e = load_elf_proc(program_file);
	if(e) e();

    return 0;
}

extern "C" void _start(){
	int ret=main();
	bt_exit(ret);
}