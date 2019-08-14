#include <btos.h>
#include <btos/shm.hpp>
#include <gds/libgds.h>
#include <gds/surface.hpp>
#include "libgds_internal.hpp"
#include "ok_png.h"

#include <cstring>
#include <malloc.h>
#include <unistd.h>

using namespace btos_api::gds;

extern "C" uint64_t GDS_LoadPNG(int fd){
	FILE *file = fdopen(dup(fd), "rb");
	ok_png *image = ok_png_read(file, OK_PNG_INFO_ONLY);
	if(image && file){
		size_t width = image->width;
		size_t height = image->height;
		size_t pixels = width * height;
		ok_png_free(image);
		fseek(file, 0, SEEK_SET);
		
		auto space = SHMSpace(bt_shm_flags::Normal);
		uint64_t shmRegion = space.ID();
		
		size_t size = pixels * 4;
		size_t pages = size / 4096;
		if(pages < size) ++pages;
		uint8_t *data = (uint8_t*)memalign(4096, pages * 4096);
		
		auto mapping = SHMMapping(shmRegion, (void*)data, 0, pages, bt_shm_flags::Normal);
		image = ok_png_read_to_buffer(file, data, 0, OK_PNG_COLOR_FORMAT_BGRA);
		fclose(file);
		
		Surface shmSurf(gds_SurfaceType::Memory, width, height, 100, gds_ColourType::True | gds_ColourType::SHM_Alpha255, shmRegion, 0);
		uint64_t bmpSurf = GDS_NewSurface(gds_SurfaceType::Bitmap, width, height, 100, gds_ColourType::True);
		GDS_SelectSurface(bmpSurf);
		GDS_Blit(shmSurf.GetID(), 0, 0, width, height, 0, 0, width, height, 100, gds_BlitFlags::Overwrite);
		//This also frees 'data'
		ok_png_free(image);
		return bmpSurf;
	}else{
		if(file) fclose(file);
		if(image) ok_png_free(image);
		return 0;
	}
}