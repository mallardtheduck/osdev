#include <btos.h>
#include <stdio.h>
#include <crt_support.h>
#include <stdlib.h>

int main(int argc, char **argv){
    if(argc < 4){
        printf("Usage: %s name device filesystem\n", argv[0]);
        return 1;
    }
    bt_mount(argv[1], argv[2], argv[3]);
    return 0;
}