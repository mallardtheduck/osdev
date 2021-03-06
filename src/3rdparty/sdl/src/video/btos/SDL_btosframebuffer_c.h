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

extern int SDL_BTOS_CreateWindowFramebuffer(_THIS, SDL_Window * window, Uint32 * format, void ** pixels, int *pitch);
extern int SDL_BTOS_UpdateWindowFramebuffer(_THIS, SDL_Window * window, const SDL_Rect * rects, int numrects);
extern void SDL_BTOS_DestroyWindowFramebuffer(_THIS, SDL_Window * window);
extern void SDL_BTOS_DestroyWindow(_THIS, SDL_Window * window);
extern int SDL_BTOS_CreateWindow(_THIS, SDL_Window *window);
extern void BTOS_PumpEvents(_THIS);
extern void SDL_BTOS_SetWindowTitle(_THIS, SDL_Window * window);

typedef struct{
	bool fail;
	bt_handle_t shm_handle;
	uint64_t shm_id;
	uint64_t gds_id;
	uint32_t *buffer;
	bt_handle_t mapping;
	uint64_t wm_id;
	SDL_Window *sdlwin;
} SDL_BTOS_windowdata;

extern SDL_BTOS_windowdata **btos_windows;
extern int btos_window_count;

/* vi: set ts=4 sw=4 expandtab: */
