#include "../../include/btos_stubs.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

char stdout_device[255]={'D', 'E', 'V', ':', '/'};
bt_filehandle stdout=0;
char stdin_device[255]={'D', 'E', 'V', ':', '/'};
bt_filehandle stdin=0;

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

void get_string(char *buffer, size_t bytes){
	if(!stdin){
		if(!bt_getenv("INPUT_DEVICE", &stdin_device[5], 250)) return;
		stdin=bt_fopen(stdin_device, 0);
	}
	size_t i=0;
	char x[2]={'a', '\0'};
	char c;
	while(true){
		bt_fread(stdin, 1, &c);
		x[0]=bt_fioctl(stdin, 2, 1, &c);
		print_string(x);
		if(x[0]) buffer[i++]=x[0];
		if(x[0]=='\n' || i==bytes) return;
	}
}

void dir_listing(){
	print_string("Directory listing of \"INIT:/\":\n");
	bt_dirhandle dir=bt_dopen("INIT:/", 0);
	directory_entry entry=bt_dread(dir);
	while(entry.valid){
		print_string(entry.filename);
		print_string("\n");
		entry=bt_dread(dir);
	}
	bt_dclose(dir);
}

void file_contents(){
	print_string("Contents of \"INIT:/config.ini\":\n");
	bt_filehandle file=bt_fopen("INIT:/config.ini", 0);
	char c;
	while(bt_fread(file, 1, &c)){
		char d[2]={c, 0};
		print_string(d);
	}
	bt_fclose(file);
}

void mount_test(){
	void *q=bt_alloc_pages(1);
	bt_free_pages(q, 1);
	bt_mount("TEST", "NULL", "INITFS");
	bt_unmount("TEST");
}

int main(int argc, char **argv){
	bt_zero("~~~Userspace test program start!~~~\n");
	print_string("TEST Command Prompt!\n");
	while(true){
		char input[128]={0};
		print_string("[TEST]>");
		get_string(input, 128);
		if(input[0]=='d') dir_listing();
		else if(input[0]=='f') file_contents();
		else if(input[0]=='m') mount_test();
		else if(input[0]=='q') break;
		else {
			print_string("Unrecognised command.");
		}

	}
	bt_zero("~~~Userspace test program done!~~~\n");
	bt_exit(0);
    return 0;
}