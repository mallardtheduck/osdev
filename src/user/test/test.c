#include "../../include/btos_stubs.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

char stdout_device[255]={'D', 'E', 'V', ':', '/'};
bt_filehandle stdout=0;

size_t strlen(const char *s){
    int ret=0;
    while(s && s[ret]) ++ret;
    return ret;
}

void print_string(const char *s){
	if(!stdout){
		if(!bt_getenv("DISPLAY_DEVICE", &stdout_device[5], 250)) return;
    	stdout=bt_fopen(stdout_device, 0);
    }
    bt_fwrite(stdout, strlen(s), s);
}

int main(int argc, char **argv){
	bt_zero("~~~Userspace test program start!~~~\n");
	print_string("Hello world!\n");
	void *q=bt_alloc_pages(1);
	bt_free_pages(q, 1);
	bt_mount("TEST", "NULL", "INITFS");
	bt_unmount("TEST");

	print_string("Directory listing of \"INIT:/\":\n");
	bt_dirhandle dir=bt_dopen("INIT:/", 0);
	directory_entry entry=bt_dread(dir);
	while(entry.valid){
		print_string(entry.filename);
		print_string("\n");
		entry=bt_dread(dir);
	}
	bt_dclose(dir);

	print_string("Contents of \"INIT:/config.ini\":\n");
	bt_filehandle file=bt_fopen("INIT:/config.ini", 0);
	char c;
	while(bt_fread(file, 1, &c)){
		char d[2]={c, 0};
		print_string(d);
	}
	bt_fclose(file);

	bt_zero("~~~Userspace test program done!~~~\n");
	btos_call(BT_EXIT, 0, 0, 0);
    return 0;
}