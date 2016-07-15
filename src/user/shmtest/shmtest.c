#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <btos.h>
#include <unistd.h>

int main(int argc, char **argv){
    if(argc == 1){
		bt_handle_t shm_space = bt_create_shm();
		uint64_t id = bt_shm_id(shm_space);
		printf("Space ID: %llu\n", id);
		void *maparea = memalign(4096, 4096);
		bt_shm_map(id, maparea, 0, 4096);
		memset(maparea, 0, 4096);
		while(1){
			printf("%s\n", (char*)maparea);
			usleep(1000000);
		}
	}else if(argc == 3){
		int a;
        sscanf(argv[1], "%i", &a);
		uint64_t id = a;
		void *maparea = memalign(4096, 4096);
		bt_shm_map(id, maparea, 0, 4096);
		strcpy(maparea, argv[2]);
	}
    return 0;
}