#include <stdio.h>
#include <stdlib.h>
#include <btos_stubs.h>

int main(){
	char *buffer=(char*)malloc(128);
	sprintf(buffer, "Hello world!\n");
	printf("%s\n", buffer);
	return 42;
}