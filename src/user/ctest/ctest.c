#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <btos_api.h>
#include <btos_stubs.h>
#include <ioctl.h>

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
    bt_filehandle file=bt_fopen("DEV:/KTEXT0", FS_Read);
    int type=bt_fioctl(file, bt_ioctl_DevType, 0, NULL);
    char desc[128];
    bt_fioctl(file, bt_ioctl_DevDesc, 128, desc);
    printf("%x - %s\n", type, desc);
    bt_fclose(file);
	return 42;
}