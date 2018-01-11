#include "pointers.hpp"
#include <cstdlib>
#include <cstring>

static bt_terminal_pointer_bitmap *expand_pointer_bmp(uint8_t bits, const bt_terminal_pointer_bitmap &p8){
	size_t pxlsize = bits / 8;
	size_t datasize = pxlsize * (p8.w * p8.h);
	bt_terminal_pointer_bitmap *bmp = (bt_terminal_pointer_bitmap*)malloc(sizeof(bt_terminal_pointer_bitmap) + datasize);
	bmp->w = p8.w;
	bmp->h = p8.h;
	bmp->bpp = bits;
	bmp->transparent = p8.transparent;
	bmp->spot_x = p8.spot_x;
	bmp->spot_y = p8.spot_y;
	bmp->datasize = datasize;
	for(size_t i = 0, j = 0; i < p8.datasize && j < bmp->datasize; ++i, j+=pxlsize){
		uint8_t p = p8.data[i];
		memset(&bmp->data[j], p, pxlsize);
	}
	return bmp;
}

bt_terminal_pointer_bitmap *get_pointer_bmp_16bpp(){
	return expand_pointer_bmp(16, pointer_bmp_8bpp);
}

bt_terminal_pointer_bitmap *get_pointer_bmp_24bpp(){
	return expand_pointer_bmp(24, pointer_bmp_8bpp);
}

bt_terminal_pointer_bitmap *get_pointer_bmp_32bpp(){
	return expand_pointer_bmp(32, pointer_bmp_8bpp);
}

