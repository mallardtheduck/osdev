#include <stdio.h>

int main(){
	static char buffer[128];
	sprintf(buffer, "Hello world!\n");
	return 42;
}