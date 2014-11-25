#include <stdio.h>
#include <btos_stubs.h>
#include <crt_support.h>
#include <stdlib.h>

int main(int argc, char **argv){
    if(argc < 2){
        printf("Usage: %s filename [params]\n", argv[0]);
        return 1;
    }
    char path[BT_MAX_PATH];
    if(btos_path_parse(argv[1], path, BT_MAX_PATH)) {
        bt_load_module(path, argc>2?argv[2]:"");
    }
    return 0;
}