#include <stdio.h>
#include <btos_stubs.h>

int main(){
	static char buffer[128];
	sprintf(buffer, "Hello world!\n");
	bt_zero(buffer);
	return 42;
}