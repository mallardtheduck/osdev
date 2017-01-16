#include <btos.h>
#include <stdio.h>

int main(int argc, char **argv){
	if(argc < 3){
		printf("Usage: %s filesystem device\n", argv[0]);
		return 1;
	}
	char *filesystem = argv[1];
	char *device = argv[2];
	printf("Formatting %s as %s...\n", device, filesystem);
	bool result = bt_format(filesystem, device, NULL);
	if(result){
		printf("Success.\n");
	}else{
		printf("Failed.\n");
	}
	return 0;
}