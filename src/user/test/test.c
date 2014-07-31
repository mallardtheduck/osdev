#include "../../include/btos_stubs.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

int main(int argc, char **argv){
	bt_zero("Hello world!\n");
	void *q=bt_alloc_pages(1);
	bt_free_pages(q, 1);
	bt_mount("TEST", "NULL", "INITFS");
	bt_unmount("TEST");
	bt_zero("All done.\n");
	btos_call(BT_EXIT, 0, 0, 0);
    return 0;
}