#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    if(argc < 2) return 1;
    char *name=argv[1];
    char **params=NULL;
    if(argc > 2) params=&argv[2];
    while(1){
        int res=execve(name, params, NULL);
        if(res<0) break;
        else wait(NULL);
    }
    return 0;
}