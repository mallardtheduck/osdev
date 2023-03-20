#include <stdio.h>

char *teststring = "HELLO WORLD!";

__attribute__ ((constructor)) static void ell_init(){
	printf("ELL INIT\n");
}

int ell_func(){
	return 42;
}