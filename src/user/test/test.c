#include "btos_stubs.h"
#include "keyboard.h"

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

void memset(void *ptr, int value, size_t n){
	for(size_t i=0; i<n; ++i){
		*((char*)ptr+i)=value;
	}
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
	size_t pos=bt_fseek(stdout, 0, true);
	size_t i=0;
	char x[2]={'a', '\0'};
	uint32_t c;
	while(true){
		bt_fread(stdin, sizeof(c), (char*)&c);
		x[0]=KB_char(c);
		if(x[0]==0x08){
		 	if(i>0) buffer[--i]=0;
		}else if(x[0]) buffer[i++]=x[0];

		if(x[0]=='\n' || i==bytes){
			print_string("\n");
			return;
		}

		bt_fseek(stdout, pos, false);
		print_string(buffer);
		size_t newpos=bt_fseek(stdout, 0, true);
		print_string(" ");
		bt_fseek(stdout, newpos, false);
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

void dir_listing2(char *input){
	input[strlen(input)-1]=0;
	print_string("Directory listing of \"");
	print_string(&input[2]);
	print_string("\":\n");
	bt_dirhandle dir=bt_dopen(&input[2], 0);
	if(!dir) return;
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
	char c[32]={0};
	while(bt_fread(file, 31, c)){
		print_string(c);
		memset(c, 0, 32);
	}
	bt_fclose(file);
}

void file_contents2(char *input){
	input[strlen(input)-1]=0;
	print_string("Contents of \"");
	print_string(&input[2]);
	print_string("\":\n");
	bt_filehandle file=bt_fopen(&input[2], 0);
	if(!file) return;
	char c[32]={0};
	while(bt_fread(file, 31, c)){
		print_string(c);
		memset(c, 0, 32);
	}
	bt_fclose(file);
}

void mount_test(){
	void *q=bt_alloc_pages(1);
	bt_free_pages(q, 1);
	bt_mount("TEST", "NULL", "INITFS");
	bt_unmount("TEST");
}

void version(){
	print_string("BT/OS TEST Command prompt.\n");
	print_string("For testing only.\n");
}

int main(int argc, char **argv){
	bt_zero("~~~Userspace test program start!~~~\n");
	print_string("TEST Command Prompt!\n");
	while(true){
		char input[128]={0};
		print_string("[TEST]>");
		get_string(input, 128);
		if(input[0]=='d') dir_listing();
		else if(input[0]=='l') dir_listing2(input);
		else if(input[0]=='f') file_contents();
		else if(input[0]=='c') file_contents2(input);
		else if(input[0]=='m') mount_test();
		else if(input[0]=='v') version();
		else if(input[0]=='q') break;
		else {
			if(strlen(input) && input[0]!='\n') print_string("Unrecognised command.\n");
		}
	}
	bt_zero("~~~Userspace test program done!~~~\n");
	bt_exit(0);
    return 0;
}