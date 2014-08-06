#ifndef _KEYCODES_HPP
#define _KEYCODES_HPP

#include <stdint.h>
#include <stddef.h>

namespace KeyFlags{
	enum Enum{
		KeyUp		= 1 << 15,
		Shift		= 1 << 14,
		Control		= 1 << 13,
		Alt			= 1 << 12,
		Meta		= 1 << 11,
		CapsLock	= 1 << 10,
		NumLock		= 1 << 9,
		ScrollLock	= 1 << 8,
		NonASCII	= 1 << 7,
	};
}

const uint16_t KC_Mask=0x7F;

namespace KeyCodes{
	enum Enum{
		Escape		= 0x01,
		PrintScreen = 0x02,
		ScrollLock	= 0x03,
		Break		= 0x04,
		Delete		= 0x05,
		Home		= 0x06,
		End			= 0x07,
		PageUp		= 0x08,
		PageDown	= 0x09,
		CapsLock	= 0x10,
		NumLock		= 0x0A,
		Control		= 0x0B,
		Alt			= 0x0C,
		Meta		= 0x0D,
		Insert		= 0x0E,
		AltGr		= 0x0F,
		Menu		= 0x10,
		UpArrow		= 0x11,
		DownArrow	= 0x12,
		LeftArrow	= 0x13,
		RightArrow	= 0x14,
		Shift		= 0x15,

		Unicode		= 0x60,

		F1			= 0x70,
		F2			= 0x71,
		F3			= 0x72,
		F4			= 0x73,
		F5			= 0x74,
		F6			= 0x75,
		F7			= 0x76,
		F8			= 0x77,
		F9			= 0x78,
		F10			= 0x79,
		F11			= 0x7A,
		F12			= 0x7B,
		F13			= 0x7C,
		F14			= 0x7D,
		F15			= 0x7E,
		F16			= 0x7F,
	};
}

typedef uint16_t key_info[3];
const size_t KI_Normal=0;
const size_t KI_Shift=1;
const size_t KI_AltGr=2;

#endif