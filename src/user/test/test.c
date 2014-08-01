#include "../../include/btos_stubs.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

size_t strlen(const char *s){
    int ret=0;
    while(s && s[ret]) ++ret;
    return ret;
}

void print_string(const char *s){
    bt_filehandle f=btos_call(BT_FOPEN, (uint32_t)"DEV:/VGATEXT0", 0, 0);
    btos_call(BT_FWRITE, f, strlen(s), (uint32_t)s);
    btos_call(BT_FCLOSE, f, 0, 0);
}

int main(int argc, char **argv){
	//bt_zero("Hello world!\n");
	print_string("Hello world!\n");
	void *q=bt_alloc_pages(1);
	bt_free_pages(q, 1);
	bt_mount("TEST", "NULL", "INITFS");
	bt_unmount("TEST");
	bt_zero("All done.\n");
	btos_call(BT_EXIT, 0, 0, 0);
    return 0;
}