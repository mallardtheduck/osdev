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
#include "SDL_hints.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define BTOS_SURFACE   "_SDL_BTOSSurface"

SDL_BTOS_windowdata **btos_windows;
int btos_window_count;

static void _SDL_BTOS_AddWindow(SDL_BTOS_windowdata *data){
	if(btos_window_count == 0){
		btos_windows = malloc(sizeof(SDL_BTOS_windowdata*));
		btos_windows[0] = data;
		++btos_window_count;
	}else{
		btos_windows = realloc(btos_windows, ++btos_window_count * sizeof(SDL_BTOS_windowdata*));
		btos_windows[btos_window_count - 1] = data;
	}
}

static void _SDL_BTOS_RemoveWindow(SDL_BTOS_windowdata *data){
	bool removed = false;
	for(int i = 0; i < btos_window_count; ++i){
		if(removed) btos_windows[i - 1] = btos_windows[i];
		if(btos_windows[i] == data)	removed = true;
	}
	--btos_window_count;
	if(btos_window_count > 0){
		realloc(btos_windows, btos_window_count * sizeof(SDL_BTOS_windowdata*));
	}else{
		free(btos_windows);
	}
}

static SDL_BTOS_windowdata _SDL_BTOS_CreateWindow(SDL_Window * window){
	size_t w = window->w;
	size_t h = window->h;
	
	SDL_BTOS_windowdata info;
	info.sdlwin = window;
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
    bt_zero("SDL: Configured SHM.\n");
    
    info.gds_id = GDS_NewSurface(gds_SurfaceType_Memory, w, h, 100, gds_ColourType_True | gds_ColourType_AlphaDisable, info.shm_id, 0);
    bt_zero("SDL: Created surface.\n");
    wm_WindowInfo wminfo;
    wminfo.x = 0;
    wminfo.y = 0;
    wminfo.options = wm_WindowOptions_Default;
    wminfo.subscriptions = wm_KeyboardEvents | wm_PointerEvents | wm_FrameEvents;
    wminfo.gds_id = info.gds_id;
    if(window->title) {
    	strncpy(wminfo.title, window->title, WM_TITLE_MAX);
    }else{
    	strcpy(wminfo.title, "SDL Window");
    }
    bt_zero("SDL: Creating window.\n");
    info.wm_id = WM_CreateWindow(wminfo);
    info.fail = false;
    bt_zero("SDL: Created window.\n");
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
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
	_SDL_BTOS_AddWindow(data);
	return 0;
}

int SDL_BTOS_CreateWindowFramebuffer(_THIS, SDL_Window * window, Uint32 * format, void ** pixels, int *pitch)
{
    const Uint32 surface_format = SDL_PIXELFORMAT_ARGB8888;
    int w, h;
    int bpp;
    Uint32 Rmask, Gmask, Bmask, Amask;

    /* Free the old framebuffer surface */
    SDL_BTOS_DestroyWindowFramebuffer(_this, window);

    /* Create a new one */
    SDL_PixelFormatEnumToMasks(surface_format, &bpp, &Rmask, &Gmask, &Bmask, &Amask);
    SDL_GetWindowSize(window, &w, &h);
    //printf("bpp: %i, Rmask:  %x, Gmask: %x, Bmask: %x, Amask: %x\n", bpp, Rmask, Gmask, Bmask, Amask);
    
    SDL_BTOS_windowdata *info = (SDL_BTOS_windowdata*)window->driverdata;
    
    *format = surface_format;
    *pixels = info->buffer;
    *pitch = w * 4;
    return 0;
}

int SDL_BTOS_UpdateWindowFramebuffer(_THIS, SDL_Window * window, const SDL_Rect * rects, int numrects)
{
	//printf("SDL_BTOS_UpdateWindowFramebuffer\n");
	//printf("window: %p, rects: %p, numrects: %i\n", window, rects, numrects);
	SDL_BTOS_windowdata *info = (SDL_BTOS_windowdata*)window->driverdata;
	WM_SelectWindow(info->wm_id);
	
    for(int i = 0; i < numrects; ++i){
    	WM_UpdateRect(rects[i].x, rects[i].y, rects[i].w, rects[i].h);
    	//printf("rect: %i - (%i, %i, %i, %i)\n", i, rects[i].x, rects[i].y, rects[i].w, rects[i].h);
    }

    return 0;
}

void SDL_BTOS_DestroyWindowFramebuffer(_THIS, SDL_Window * window)
{
	// Does nothing; descruction done on DestroyWindow below
}

void SDL_BTOS_DestroyWindow(_THIS, SDL_Window * window)
{
    SDL_BTOS_windowdata *info = (SDL_BTOS_windowdata*)window->driverdata;

    if(info){
    	WM_SelectWindow(info->wm_id);
    	WM_DestroyWindow();
    	GDS_SelectSurface(info->gds_id);
    	GDS_DeleteSurface();
    	bt_closehandle(info->mapping);
    	SDL_free(info->buffer);
    	bt_closehandle(info->shm_handle);
    	_SDL_BTOS_RemoveWindow(info);
    	SDL_free(info);
    }
}

void SDL_BTOS_SetWindowTitle(_THIS, SDL_Window * window){
	SDL_BTOS_windowdata *info = (SDL_BTOS_windowdata*)window->driverdata;
	if(info && window->title){
		WM_SelectWindow(info->wm_id);
		WM_SetTitle(window->title);
	}
}

#endif /* SDL_VIDEO_DRIVER_BTOS */

/* vi: set ts=4 sw=4 expandtab: */
