#include <btos.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    if(argc < 2){
        printf("Usage: %s pid\n", argv[0]);
        return 1;
    }
    bt_pid_t pid=atoi(argv[1]);
    if(!pid) return 1;
    bt_kill(pid);
    return 0;
}