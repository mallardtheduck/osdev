#include "btos_stubs.h"
#include "keyboard.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#pragma GCC diagnostic ignored "-Wunused-parameter"

char bt_stdout_device[255]={'D', 'E', 'V', ':', '/'};
bt_filehandle bt_stdout=0;
char bt_stdin_device[255]={'D', 'E', 'V', ':', '/'};
bt_filehandle bt_stdin=0;

bool btos_path_parse(char *opath, char *bufffer, size_t size);

void print_string(const char *s){
	if(!bt_stdout){
		if(!bt_getenv("DISPLAY_DEVICE", &bt_stdout_device[5], 250)) return;
    	bt_stdout=bt_fopen(bt_stdout_device, FS_Write);
    }
    bt_fwrite(bt_stdout, strlen(s), s);
}

void get_string(char *buffer, size_t bytes){
	if(!bt_stdin){
		if(!bt_getenv("INPUT_DEVICE", &bt_stdin_device[5], 250)) return;
		bt_stdin=bt_fopen(bt_stdin_device, FS_Read);
	}
	size_t pos=bt_fseek(bt_stdout, 0, true);
	size_t i=0;
	char x[2]={'a', '\0'};
	uint32_t c;
	while(true){
		bt_fread(bt_stdin, sizeof(c), (char*)&c);
		x[0]=KB_char(c);
		if(x[0]==0x08){
		 	if(i>0) buffer[--i]=0;
		}else if(x[0]) buffer[i++]=x[0];

		if(x[0]=='\n' || i==bytes){
			print_string("\n");
			return;
		}

		bt_fseek(bt_stdout, pos, false);
		print_string(buffer);
		size_t newpos=bt_fseek(bt_stdout, 0, true);
		print_string(" ");
		bt_fseek(bt_stdout, newpos, false);
	}
}

void dir_listing(){
	print_string("Directory listing of \"INIT:/\":\n");
	bt_dirhandle dir=bt_dopen("INIT:/", FS_Read);
	bt_directory_entry entry=bt_dread(dir);
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
	bt_dirhandle dir=bt_dopen(&input[2], FS_Read);
	if(!dir) return;
	bt_directory_entry entry=bt_dread(dir);
	while(entry.valid){
		print_string(entry.filename);
		print_string("\n");
		entry=bt_dread(dir);
	}
	bt_dclose(dir);
}

void file_contents(){
	print_string("Contents of \"INIT:/config.ini\":\n");
	bt_filehandle file=bt_fopen("INIT:/config.ini", FS_Read);
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
	bt_filehandle file=bt_fopen(&input[2], FS_Read);
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

void ata_test(){
	char buf[513]={0};
	bt_filehandle ata=bt_fopen("DEV:/ATA0P0", FS_Read);
	bt_fread(ata, 512, buf);
	print_string("The contents of the first sector of the ATA0P0 device is:\n");
	print_string(buf);
	print_string("\n");
	bt_fread(ata, 512, buf);
	print_string("The contents of the second sector of the ATA0P0 device is:\n");
	print_string(buf);
	bt_fclose(ata);
	print_string("\n");
}

void run_program(char *input){
	input[strlen(input)-1]=0;
	print_string("Running ");
	print_string(&input[2]);
	print_string("\n");
	bt_pid pid=bt_spawn(&input[2], 0, NULL);
	if(pid) bt_wait(pid);
}

void path(char *input){
	char buffer[BT_MAX_PATH]={0};
	if(btos_path_parse(&input[2], buffer, BT_MAX_PATH)){
		print_string(buffer);
		print_string("\n");
	}else print_string("Failed.\n");
}

bt_lockhandle screenlock;

void the_thread(void *p){
    (void)p;
    bt_lock(screenlock);
    printf("New thread started!\n");
    bt_unlock(screenlock);
    bt_yield();
    bt_end_thread();
}

void thread_test(){
    screenlock=bt_create_lock();
    for(size_t k=0; k<1000; ++k) {
        bt_threadhandle threads[10]={0};
        void *threadstacks[10]={0};
        for(size_t i=0; i<10; ++i) {
            threadstacks[i] = malloc(4096);
            void *stackptr = (void *) ((char *) threadstacks[i] + 4096);
            char *testparam = "TEST PARAMETER";
            threads[i] = bt_new_thread(&the_thread, (void *) testparam, stackptr);
            bt_lock(screenlock);
            printf("New thread handle: %i\n", threads[i]);
            bt_unlock(screenlock);
        }
        for(size_t i=0; i<10; ++i) {
            bt_wait_thread(threads[i]);
            free(threadstacks[i]);
        }
    }
    bt_destroy_lock(screenlock);
}

void crash_test(){
    // - CRASH METHOD 1: Access unmapped memory (segfault-ish)
    //char *q=(char*)0xDEADBEEF;
    //*q='q';
    // - CRASH METHOD 2: Try to jump to null pointer
    //void (*q)()=(void(*)())0;
    //q();
    // - CRASH METHOD 3: Divide by zero
    int i=0;
    int z=100/i;
    (void)z;
}

int main(int argc, char **argv){
	bt_zero("~~~Userspace test program start!~~~\n");
	print_string("TEST Command Prompt!\n");
	while(true){
		char input[128]={0};
		print_string("[TEST]>");
		get_string(input, 128);
		if(input[0]=='d') dir_listing();
		else if(input[0]=='b') ata_test();
		else if(input[0]=='l') dir_listing2(input);
		else if(input[0]=='f') file_contents();
		else if(input[0]=='c') file_contents2(input);
		else if(input[0]=='m') mount_test();
		else if(input[0]=='v') version();
		else if(input[0]=='r') run_program(input);
		else if(input[0]=='p') path(input);
		else if(input[0]=='t') thread_test();
        else if(input[0]=='x') crash_test();
		else if(input[0]=='q') break;
		else {
			if(strlen(input) && input[0]!='\n') print_string("Unrecognised command.\n");
		}
	}
	bt_zero("~~~Userspace test program done!~~~\n");
	bt_exit(0);
    return 0;
}