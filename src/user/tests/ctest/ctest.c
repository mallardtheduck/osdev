#include <btos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dev/video_dev.h>
#include <crt_support.h>
#include <dev/rtc.h>

__attribute__ ((constructor)) void cons_test(void)
{
	printf("Global constructor...\n");
}

__attribute__ ((destructor)) void dest_test(void)
{
	printf("Global destructor...\n");
}

int main(int argc, char **argv){
	printf("CTEST: %i, %p\n", argc, argv);
	for(int i=0; i<argc; ++i){
		printf("Arg %i: %s\n", i, argv[i]);
	}
	char *buffer=(char*)malloc(128);
	sprintf(buffer, "Hello world!");
	printf("%s\n", buffer);
	memset(buffer, 0, 128);
	FILE *fd=fopen("INFO:/PROCS", "r");
	while(fgets(buffer, 128, fd)==buffer){
		printf("%s", buffer);
		memset(buffer, 0, 128);
	}
	fclose(fd);
    bt_filehandle file=btos_get_handle(fileno(stdout));
    size_t type=bt_fioctl(file, bt_ioctl_DevType, 0, NULL);
    char desc[128];
    bt_fioctl(file, bt_ioctl_DevDesc, 128, desc);
    printf("%x - %s\n", (int)type, desc);
    bt_vidmode mode;
    char bg=1, fg=15;
    uint8_t colour=(uint8_t)bt_fioctl(file, bt_vid_ioctl_GetTextColours, 0, NULL);
    uint8_t col=(uint8_t)((bg << 4) | fg);
    bt_fioctl(file, bt_vid_ioctl_SetTextColours, 1, (char*)&col);
    bt_fioctl(file, bt_vid_ioctl_QueryMode, sizeof(mode), (char*)&mode);
    //bt_fioctl(file, bt_vid_ioctl_ClearScreen, 0, NULL);
    printf("Video mode: %ix%i %ibpp text:%i, pal:%i, colours:%02x\n", mode.width, mode.height, mode.bpp, mode.textmode, mode.palette, (int)colour);
    bg=0; fg=7;
    bt_fioctl(file, bt_vid_ioctl_SetTextColours, sizeof(colour), (char*)&colour);
    /*char *memory=malloc(32768);
    bt_mmap(file, 0, memory, (80*25));
    strcpy(memory+40, "Hello world!");
    bt_fflush(file);*/
    uint64_t start = bt_rtc_millis();
    for(size_t i = 0; i < 1000; ++i) bt_yield();
    uint64_t end = bt_rtc_millis();
    printf("Schedulter benchmark: %i\n", (int)(end - start));
    bt_handle_t a = bt_create_atom(1);
    printf("Atom value: %i\n", (int)bt_read_atom(a));
    bt_cmpxchg_atom(a, 1, 2);
    printf("Atom value: %i\n", (int)bt_read_atom(a));
    bt_cmpxchg_atom(a, 1, 3);
    printf("Atom value: %i\n", (int)bt_read_atom(a));
	return 42;
}
