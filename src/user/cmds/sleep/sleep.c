#include <stdio.h>
#include <stdlib.h>
#include <dev/rtc.h>
#include <btos/bt_msg.h>

int main(int argc, char **argv){
	if(argc != 2){
		printf("Usage: %s msec\n", argv[0]);
		return 0;
	}
	uint32_t msec = strtoul(argv[1], NULL, 0);
	bt_rtc_sleep(msec);
}