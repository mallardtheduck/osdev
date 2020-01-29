#include "../../SDL_internal.h"

#if SDL_VIDEO_DRIVER_BTOS

#include <wm/libwm.h>
#include <dev/keyboard.h>
#include <ctype.h>

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

#define KEYCODE_MAP(x, y) case x: sdl_key = y; break

static void _BTOS_HandleKeyboardEvent(wm_Event *event){
	int sdl_key = 0;
	uint16_t keycode = KB_code(event->Key.code);
	if(keycode && (keycode & KeyFlags_NonASCII)){
		switch((char)keycode & KC_Mask){
			KEYCODE_MAP(KeyCodes_Escape, SDL_SCANCODE_ESCAPE);
			KEYCODE_MAP(KeyCodes_PrintScreen, SDL_SCANCODE_PRINTSCREEN);
			KEYCODE_MAP(KeyCodes_ScrollLock, SDL_SCANCODE_SCROLLLOCK);
			KEYCODE_MAP(KeyCodes_Break, SDL_SCANCODE_PAUSE);
			KEYCODE_MAP(KeyCodes_Delete, SDL_SCANCODE_DELETE);
			KEYCODE_MAP(KeyCodes_Home, SDL_SCANCODE_HOME);
			KEYCODE_MAP(KeyCodes_End, SDL_SCANCODE_END);
			KEYCODE_MAP(KeyCodes_PageUp, SDL_SCANCODE_PAGEUP);
			KEYCODE_MAP(KeyCodes_PageDown, SDL_SCANCODE_PAGEDOWN);
			KEYCODE_MAP(KeyCodes_CapsLock, SDL_SCANCODE_CAPSLOCK);
			KEYCODE_MAP(KeyCodes_NumLock, SDL_SCANCODE_NUMLOCKCLEAR);
			case KeyCodes_Control:
				if(keycode & KeyFlags_Right) sdl_key = SDL_SCANCODE_RCTRL;
				else sdl_key = SDL_SCANCODE_LCTRL;
				break;
			case KeyCodes_Alt:
				if(keycode & KeyFlags_Right) sdl_key = SDL_SCANCODE_RALT;
				else sdl_key = SDL_SCANCODE_LALT;
				break;
			KEYCODE_MAP(KeyCodes_Insert, SDL_SCANCODE_INSERT);
			KEYCODE_MAP(KeyCodes_AltGr, SDL_SCANCODE_RALT);
			case KeyCodes_Meta:
				if(keycode & KeyFlags_Right) sdl_key = SDL_SCANCODE_RGUI;
				else sdl_key = SDL_SCANCODE_LGUI;
				break;
			KEYCODE_MAP(KeyCodes_Menu, SDL_SCANCODE_MENU);
			KEYCODE_MAP(KeyCodes_UpArrow, SDL_SCANCODE_UP);
			KEYCODE_MAP(KeyCodes_DownArrow, SDL_SCANCODE_DOWN);
			KEYCODE_MAP(KeyCodes_LeftArrow, SDL_SCANCODE_LEFT);
			KEYCODE_MAP(KeyCodes_RightArrow, SDL_SCANCODE_RIGHT);
			case KeyCodes_Shift:
				if(keycode & KeyFlags_Right) sdl_key = SDL_SCANCODE_RSHIFT;
				else sdl_key = SDL_SCANCODE_LSHIFT;
				break;
			KEYCODE_MAP(KeyCodes_F1, SDL_SCANCODE_F1);
			KEYCODE_MAP(KeyCodes_F2, SDL_SCANCODE_F2);
			KEYCODE_MAP(KeyCodes_F3, SDL_SCANCODE_F3);
			KEYCODE_MAP(KeyCodes_F4, SDL_SCANCODE_F4);
			KEYCODE_MAP(KeyCodes_F5, SDL_SCANCODE_F5);
			KEYCODE_MAP(KeyCodes_F6, SDL_SCANCODE_F6);
			KEYCODE_MAP(KeyCodes_F7, SDL_SCANCODE_F7);
			KEYCODE_MAP(KeyCodes_F8, SDL_SCANCODE_F8);
			KEYCODE_MAP(KeyCodes_F9, SDL_SCANCODE_F9);
			KEYCODE_MAP(KeyCodes_F10, SDL_SCANCODE_F10);
			KEYCODE_MAP(KeyCodes_F11, SDL_SCANCODE_F11);
			KEYCODE_MAP(KeyCodes_F12, SDL_SCANCODE_F12);
			KEYCODE_MAP(KeyCodes_F13, SDL_SCANCODE_F13);
			KEYCODE_MAP(KeyCodes_F14, SDL_SCANCODE_F14);
			KEYCODE_MAP(KeyCodes_F15, SDL_SCANCODE_F15);
			KEYCODE_MAP(KeyCodes_F16, SDL_SCANCODE_F16);
			default:
				sdl_key = 0; break;
		}
	}else{
		switch(tolower((unsigned char)keycode)){
			KEYCODE_MAP('1', SDL_SCANCODE_1);
			KEYCODE_MAP('2', SDL_SCANCODE_2);
			KEYCODE_MAP('3', SDL_SCANCODE_3);
			KEYCODE_MAP('4', SDL_SCANCODE_4);
			KEYCODE_MAP('5', SDL_SCANCODE_5);
			KEYCODE_MAP('6', SDL_SCANCODE_6);
			KEYCODE_MAP('7', SDL_SCANCODE_7);
			KEYCODE_MAP('8', SDL_SCANCODE_8);
			KEYCODE_MAP('9', SDL_SCANCODE_9);
			KEYCODE_MAP('0', SDL_SCANCODE_0);
			
			KEYCODE_MAP('!', SDL_SCANCODE_1);
			KEYCODE_MAP('@', SDL_SCANCODE_2);
			KEYCODE_MAP('#', SDL_SCANCODE_3);
			KEYCODE_MAP('$', SDL_SCANCODE_4);
			KEYCODE_MAP('%', SDL_SCANCODE_5);
			KEYCODE_MAP('^', SDL_SCANCODE_6);
			KEYCODE_MAP('&', SDL_SCANCODE_7);
			KEYCODE_MAP('*', SDL_SCANCODE_8);
			KEYCODE_MAP('(', SDL_SCANCODE_9);
			KEYCODE_MAP(')', SDL_SCANCODE_0);
			
			KEYCODE_MAP('a', SDL_SCANCODE_A);
			KEYCODE_MAP('b', SDL_SCANCODE_B);
			KEYCODE_MAP('c', SDL_SCANCODE_C);
			KEYCODE_MAP('d', SDL_SCANCODE_D);
			KEYCODE_MAP('e', SDL_SCANCODE_E);
			KEYCODE_MAP('f', SDL_SCANCODE_F);
			KEYCODE_MAP('g', SDL_SCANCODE_G);
			KEYCODE_MAP('h', SDL_SCANCODE_H);
			KEYCODE_MAP('i', SDL_SCANCODE_I);
			KEYCODE_MAP('j', SDL_SCANCODE_J);
			KEYCODE_MAP('k', SDL_SCANCODE_K);
			KEYCODE_MAP('l', SDL_SCANCODE_L);
			KEYCODE_MAP('m', SDL_SCANCODE_M);
			KEYCODE_MAP('n', SDL_SCANCODE_N);
			KEYCODE_MAP('o', SDL_SCANCODE_O);
			KEYCODE_MAP('p', SDL_SCANCODE_P);
			KEYCODE_MAP('q', SDL_SCANCODE_Q);
			KEYCODE_MAP('r', SDL_SCANCODE_R);
			KEYCODE_MAP('s', SDL_SCANCODE_S);
			KEYCODE_MAP('t', SDL_SCANCODE_T);
			KEYCODE_MAP('u', SDL_SCANCODE_U);
			KEYCODE_MAP('v', SDL_SCANCODE_V);
			KEYCODE_MAP('w', SDL_SCANCODE_W);
			KEYCODE_MAP('x', SDL_SCANCODE_X);
			KEYCODE_MAP('y', SDL_SCANCODE_Y);
			KEYCODE_MAP('z', SDL_SCANCODE_Z);
			
			KEYCODE_MAP('`', SDL_SCANCODE_GRAVE);
			KEYCODE_MAP('-', SDL_SCANCODE_MINUS);
			KEYCODE_MAP('_', SDL_SCANCODE_MINUS);
			KEYCODE_MAP('=', SDL_SCANCODE_EQUALS);
			KEYCODE_MAP('+', SDL_SCANCODE_EQUALS);
			KEYCODE_MAP('[', SDL_SCANCODE_LEFTBRACKET);
			KEYCODE_MAP('{', SDL_SCANCODE_LEFTBRACKET);
			KEYCODE_MAP(']', SDL_SCANCODE_RIGHTBRACKET);
			KEYCODE_MAP('}', SDL_SCANCODE_RIGHTBRACKET);
			KEYCODE_MAP(';', SDL_SCANCODE_SEMICOLON);
			KEYCODE_MAP(':', SDL_SCANCODE_SEMICOLON);
			KEYCODE_MAP('\'', SDL_SCANCODE_APOSTROPHE);
			KEYCODE_MAP('"', SDL_SCANCODE_APOSTROPHE);
			KEYCODE_MAP('\\', SDL_SCANCODE_BACKSLASH);
			KEYCODE_MAP('|', SDL_SCANCODE_BACKSLASH);
			KEYCODE_MAP('/', SDL_SCANCODE_SLASH);
			KEYCODE_MAP('?', SDL_SCANCODE_SLASH);
			KEYCODE_MAP(',', SDL_SCANCODE_COMMA);
			KEYCODE_MAP('<', SDL_SCANCODE_COMMA);
			KEYCODE_MAP('.', SDL_SCANCODE_PERIOD);
			KEYCODE_MAP('>', SDL_SCANCODE_PERIOD);
			
			KEYCODE_MAP('\t', SDL_SCANCODE_TAB);
			KEYCODE_MAP('\n', SDL_SCANCODE_RETURN);
			KEYCODE_MAP(0x08, SDL_SCANCODE_BACKSPACE);
			KEYCODE_MAP(' ', SDL_SCANCODE_SPACE);
			
			default:
				sdl_key = 0; break;
		}
	}
	
	if(sdl_key) SDL_SendKeyboardKey((keycode & KeyFlags_KeyUp ? SDL_RELEASED : SDL_PRESSED), sdl_key);
}

static SDL_Window *_BTOS_GetSDLWindow(uint64_t wm_id){
	for(int i = 0; i < btos_window_count; ++i){
		if(btos_windows[i]->wm_id == wm_id) return btos_windows[i]->sdlwin;
	}
	return NULL;
}

static void _BTOS_HandlePointerEvent(wm_Event *event){
	SDL_Window *win = _BTOS_GetSDLWindow(event->window_id);
	if(win){
		switch(event->type){
			case wm_EventType_PointerMove:
				SDL_SendMouseMotion(win, 1, 0, event->Pointer.x, event->Pointer.y);
				break;
			case wm_EventType_PointerButtonDown:
				SDL_SendMouseButton(win, 1, SDL_PRESSED, event->Pointer.button);
				break;
			case wm_EventType_PointerButtonUp:
				SDL_SendMouseButton(win, 1, SDL_RELEASED, event->Pointer.button);
				break;
			case wm_EventType_PointerEnter:
				SDL_SendWindowEvent(win, SDL_WINDOWEVENT_ENTER, 0, 0);
				break;
			case wm_EventType_PointerLeave:
				SDL_SendWindowEvent(win, SDL_WINDOWEVENT_LEAVE, 0, 0);
				break; 
			default: break;
		}
	}
}

static void _BTOS_HandleFrameEvent(wm_Event *event){
	SDL_Window *win = _BTOS_GetSDLWindow(event->window_id);
	if(win){
		switch(event->type){
			case wm_EventType_Close:
				SDL_SendWindowEvent(win, SDL_WINDOWEVENT_CLOSE, 0, 0);
				break;
			default: break;
			case wm_EventType_Hide:
				WM_SelectWindow(event->window_id);
				wm_WindowInfo info = WM_WindowInfo();
				WM_ChangeOptions(info.options & ~wm_WindowOptions_Visible);
				break;
		}
	}
}

void BTOS_PumpEvents(_THIS){
	bt_msg_filter filt = WM_GetEventFilter();
	bt_msg_header msg = bt_recv_filtered(filt, false);
	if(msg.valid){
	    wm_Event event = WM_ParseMessage(&msg);
	    if(event.type & wm_KeyboardEvents){
	    	_BTOS_HandleKeyboardEvent(&event);
	    }else if(event.type & wm_PointerEvents){
	    	_BTOS_HandlePointerEvent(&event);
	    }else if(event.type & wm_FrameEvents){
	    	_BTOS_HandleFrameEvent(&event);
	    }
		bt_msg_ack(&msg);
	}
}

#endif
