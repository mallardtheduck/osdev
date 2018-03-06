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

#if SDL_VIDEO_DRIVER_BTOS

/* BTOS SDL video driver implementation; this is just enough to make an
 *  SDL-based application THINK it's got a working video driver, for
 *  applications that call SDL_Init(SDL_INIT_VIDEO) when they don't need it,
 *  and also for use as a collection of stubs when porting SDL to a new
 *  platform for which you haven't yet written a valid video driver.
 *
 * This is also a great way to determine bottlenecks: if you think that SDL
 *  is a performance problem for a given platform, enable this driver, and
 *  then see if your application runs faster without video overhead.
 *
 * Initial work by Ryan C. Gordon (icculus@icculus.org). A good portion
 *  of this was cut-and-pasted from Stephane Peter's work in the AAlib
 *  SDL video driver.  Renamed to "BTOS" by Sam Lantinga.
 */

#include "SDL_video.h"
#include "SDL_mouse.h"
#include "../SDL_sysvideo.h"
#include "../SDL_pixels_c.h"
#include "../../events/SDL_events_c.h"

#include "SDL_btosvideo.h"
//#include "SDL_btosevents_c.h"
#include "SDL_btosframebuffer_c.h"

#define BTOSVID_DRIVER_NAME "BTOS"

#pragma GCC diagnostic ignored "-Wunused-parameter"

/* Initialization/Query functions */
static int BTOS_VideoInit(_THIS);
static int BTOS_SetDisplayMode(_THIS, SDL_VideoDisplay * display, SDL_DisplayMode * mode);
static void BTOS_VideoQuit(_THIS);

/* BTOS driver bootstrap functions */

static int
BTOS_Available(void)
{
    return 1;
}

static void
BTOS_DeleteDevice(SDL_VideoDevice * device)
{
    SDL_free(device);
}

static SDL_VideoDevice *
BTOS_CreateDevice(int devindex)
{
    SDL_VideoDevice *device;

    /* Initialize all variables that we clean on shutdown */
    device = (SDL_VideoDevice *) SDL_calloc(1, sizeof(SDL_VideoDevice));
    if (!device) {
        SDL_OutOfMemory();
        return (0);
    }
    device->is_dummy = SDL_FALSE;

    /* Set the function pointers */
    device->VideoInit = BTOS_VideoInit;
    device->VideoQuit = BTOS_VideoQuit;
    device->SetDisplayMode = BTOS_SetDisplayMode;
    //device->PumpEvents = BTOS_PumpEvents;
    device->CreateSDLWindow = SDL_BTOS_CreateWindow;
    device->CreateWindowFramebuffer = SDL_BTOS_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = SDL_BTOS_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = SDL_BTOS_DestroyWindowFramebuffer;

    device->free = BTOS_DeleteDevice;

    return device;
}

VideoBootStrap BTOS_bootstrap = {
    BTOSVID_DRIVER_NAME, "SDL BTOS video driver",
    BTOS_Available, BTOS_CreateDevice
};


int
BTOS_VideoInit(_THIS)
{
    SDL_DisplayMode mode;

    /* Use a fake 32-bpp desktop mode */
    mode.format = SDL_PIXELFORMAT_RGB888;
    mode.w = 1024;
    mode.h = 768;
    mode.refresh_rate = 0;
    mode.driverdata = NULL;
    if (SDL_AddBasicVideoDisplay(&mode) < 0) {
        return -1;
    }

    SDL_zero(mode);
    SDL_AddDisplayMode(&_this->displays[0], &mode);

    /* We're done! */
    return 0;
}

static int
BTOS_SetDisplayMode(_THIS, SDL_VideoDisplay * display, SDL_DisplayMode * mode)
{
    return 0;
}

void
BTOS_VideoQuit(_THIS)
{
}

#endif /* SDL_VIDEO_DRIVER_BTOS */

/* vi: set ts=4 sw=4 expandtab: */
