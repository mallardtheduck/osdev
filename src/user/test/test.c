#include "../../include/btos_stubs.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

int main(int argc, char **argv){
	uint32_t q=btos_call(BT_ALLOC_PAGES, 1, 0, 0);
	btos_call(BT_FREE_PAGES, q, 1, 0);
	btos_call(BT_EXIT, 0, 0, 0);
    return 0;
}