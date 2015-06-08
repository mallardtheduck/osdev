#include <stdio.h>

int main(int argc, char **argv){
    (void)argv;
    printf("Crashing (div0)...\n");
    return 1 / (argc - 1);
}
