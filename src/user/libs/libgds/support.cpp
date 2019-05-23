#include <btos.h>
#include <btos/shm.hpp>
#include <gds/libgds.h>
#include <gds/surface.hpp>
#include "libgds_internal.hpp"
#include "ok_png.h"

#include <cstring>
#include <malloc.h>

using namespace btos_api::gds;

extern "C" uint64_t GDS_LoadPNG(int fd){
	FILE *file = fdopen(fd, "r");
	ok_png *image = ok_png_read(file, OK_PNG_COLOR_FORMAT_BGRA);
	if(image && file){
		size_t width = image->width;
		size_t height = image->height;
		size_t pixels = width * height;
		
		auto space = SHMSpace(bt_shm_flags::Normal);
		uint64_t shmRegion = space.ID();
		
		size_t size = pixels * 4;
		size_t pages = size / 4096;
		if(pages < size) ++pages;
		uint32_t *data = (uint32_t*)memalign(4096, pages * 4096);
		
		auto mapping = SHMMapping(shmRegion, (void*)data, 0, pages, bt_shm_flags::Normal);
		memcpy(mapping.Address(), image->data, size);
		ok_png_free(image);
		fclose(file);
		
		Surface shmSurf(gds_SurfaceType::Memory, width, height, 100, gds_ColourType::True, shmRegion, 0);
		uint64_t bmpSurf = GDS_NewSurface(gds_SurfaceType::Bitmap, width, height, 100, gds_ColourType::True);
		GDS_SelectSurface(bmpSurf);
		GDS_Blit(shmSurf.GetID(), 0, 0, width, height, 0, 0, width, height);
		return bmpSurf;
	}else{
		if(file) fclose(file);
		if(image) ok_png_free(image);
		return 0;
	}
}