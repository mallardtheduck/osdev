/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2017 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "../../SDL_internal.h"
#include <btos.h>
#include <gds/libgds.h>
#include <wm/libwm.h>
#include <malloc.h>

#if SDL_VIDEO_DRIVER_BTOS

#include "../SDL_sysvideo.h"
#include "SDL_btosframebuffer_c.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define BTOS_SURFACE   "_SDL_BTOSSurface"

typedef struct{
	bool fail;
	bt_handle_t shm_handle;
	uint64_t shm_id;
	uint64_t gds_id;
	uint32_t *buffer;
	bt_handle_t mapping;
	uint64_t wm_id;
} SDL_BTOS_windowdata;

static SDL_BTOS_windowdata _SDL_BTOS_CreateWindow(SDL_Window * window){
	size_t w = window->w;
	size_t h = window->h;
	
	SDL_BTOS_windowdata info;
	info.shm_handle = bt_create_shm(bt_shm_flags_Normal);
	if(!info.shm_handle){
		info.fail = true;
		return info;
	}
	info.shm_id = bt_shm_id(info.shm_handle);
	if(!info.shm_id){
		info.fail = true;
		return info;
	}
	
	size_t bufferSize = w * h * 4;
    size_t pages = (bufferSize / 4096) + 1;
    size_t memSize = pages * 4096;
    info.buffer = memalign(4096, memSize);
    if(!info.buffer){
    	info.fail = true;
		return info;
    }
    
    info.mapping = bt_shm_map(info.shm_id, info.buffer, 0, pages, bt_shm_flags_Normal);
    if(!info.mapping){
    	info.fail = true;
		return info;
    }
    
    info.gds_id = GDS_NewSurface(gds_SurfaceType_Memory, w, h, 100, gds_ColourType_True, info.shm_id, 0);
    wm_WindowInfo wminfo;
    wminfo.x = 0;
    wminfo.y = 0;
    wminfo.options = wm_WindowOptions_Default;
    wminfo.subscriptions = wm_KeyboardEvents | wm_PointerEvents | wm_FrameEvents;
    wminfo.gds_id = info.gds_id;
    strcpy(wminfo.title, "SDL Window");
    info.wm_id = WM_CreateWindow(wminfo);
    info.fail = false;
    return info;
}

int SDL_BTOS_CreateWindow(_THIS, SDL_Window *window){
	SDL_BTOS_windowdata *data = SDL_malloc(sizeof(SDL_BTOS_windowdata));
	if(!data) return -1;
	*data = _SDL_BTOS_CreateWindow(window);
	if(data->fail){
		SDL_free(data);
		return -1;
	}
	window->driverdata = data;
	return 0;
}

int SDL_BTOS_CreateWindowFramebuffer(_THIS, SDL_Window * window, Uint32 * format, void ** pixels, int *pitch)
{
    const Uint32 surface_format = SDL_PIXELFORMAT_RGB888;
    int w, h;
    int bpp;
    Uint32 Rmask, Gmask, Bmask, Amask;

    /* Free the old framebuffer surface */
    SDL_BTOS_DestroyWindowFramebuffer(_this, window);

    /* Create a new one */
    SDL_PixelFormatEnumToMasks(surface_format, &bpp, &Rmask, &Gmask, &Bmask, &Amask);
    SDL_GetWindowSize(window, &w, &h);
    
    SDL_BTOS_windowdata *info = (SDL_BTOS_windowdata*)window->driverdata;
    
    *format = surface_format;
    *pixels = info->buffer;
    *pitch = w * 4;
    return 0;
}

int SDL_BTOS_UpdateWindowFramebuffer(_THIS, SDL_Window * window, const SDL_Rect * rects, int numrects)
{
    /* Does nothing? */

    return 0;
}

void SDL_BTOS_DestroyWindowFramebuffer(_THIS, SDL_Window * window)
{
    /*SDL_BTOS_surfaceinfo *info;

    info = (SDL_BTOS_surfaceinfo *) SDL_SetWindowData(window, BTOS_SURFACE, NULL);
    if(info){
    	GDS_SelectSurface(info->gds_id);
    	GDS_DeleteSurface();
    	bt_closehandle(info->mapping);
    	SDL_free(info->buffer);
    	bt_closehandle(info->shm_handle);
    	SDL_free(info);
    }*/
}

#endif /* SDL_VIDEO_DRIVER_BTOS */

/* vi: set ts=4 sw=4 expandtab: */
