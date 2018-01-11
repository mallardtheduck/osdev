#ifndef _KEYCODES_HPP
#define _KEYCODES_HPP

#include <stdint.h>
#include <stddef.h>
#include <util/bt_enum.h>

ENUM_START(KeyFlags)
ENUM_SET(KeyFlags, KeyUp, 1 << 15),
ENUM_SET(KeyFlags, Shift, 1 << 14),
ENUM_SET(KeyFlags, Control, 1 << 13),
ENUM_SET(KeyFlags, Alt, 1 << 12),
ENUM_SET(KeyFlags, Meta, 1 << 11),
ENUM_SET(KeyFlags, CapsLock,1 << 10),
ENUM_SET(KeyFlags, NumLock, 1 << 9),
ENUM_SET(KeyFlags, ScrollLock, 1 << 8),
ENUM_SET(KeyFlags, NonASCII, 1 << 7),
ENUM_SET(KeyFlags, Right, 1 << 6),
ENUM_END
ENUM_TYPE(KeyFlags);

const uint16_t KC_Mask=0x3F;
const uint16_t KC_ASCIIMask=0x7F;

ENUM_START(KeyCodes)
ENUM_SET(KeyCodes, Escape, 0x01),
ENUM_SET(KeyCodes, PrintScreen, 0x02),
ENUM_SET(KeyCodes, ScrollLock, 0x03),
ENUM_SET(KeyCodes, Break, 0x04),
ENUM_SET(KeyCodes, Delete, 0x05),
ENUM_SET(KeyCodes, Home, 0x06),
ENUM_SET(KeyCodes, End, 0x07),
ENUM_SET(KeyCodes, PageUp, 0x08),
ENUM_SET(KeyCodes, PageDown, 0x09),
ENUM_SET(KeyCodes, CapsLock, 0x10),
ENUM_SET(KeyCodes, NumLock, 0x0A),
ENUM_SET(KeyCodes, Control, 0x0B),
ENUM_SET(KeyCodes, Alt, 0x0C),
ENUM_SET(KeyCodes, Meta, 0x0D),
ENUM_SET(KeyCodes, Insert, 0x0E),
ENUM_SET(KeyCodes, AltGr, 0x0F),
ENUM_SET(KeyCodes, Menu, 0x10),
ENUM_SET(KeyCodes, UpArrow, 0x11),
ENUM_SET(KeyCodes, DownArrow, 0x12),
ENUM_SET(KeyCodes, LeftArrow, 0x13),
ENUM_SET(KeyCodes, RightArrow, 0x14),
ENUM_SET(KeyCodes, Shift, 0x15),

ENUM_SET(KeyCodes, Unicode, 0x20),

ENUM_SET(KeyCodes, F1, 0x30),
ENUM_SET(KeyCodes, F2, 0x31),
ENUM_SET(KeyCodes, F3, 0x32),
ENUM_SET(KeyCodes, F4, 0x33),
ENUM_SET(KeyCodes, F5, 0x34),
ENUM_SET(KeyCodes, F6, 0x35),
ENUM_SET(KeyCodes, F7, 0x36),
ENUM_SET(KeyCodes, F8, 0x37),
ENUM_SET(KeyCodes, F9, 0x38),
ENUM_SET(KeyCodes, F10, 0x39),
ENUM_SET(KeyCodes, F11, 0x3A),
ENUM_SET(KeyCodes, F12, 0x3B),
ENUM_SET(KeyCodes, F13, 0x3C),
ENUM_SET(KeyCodes, F14, 0x3D),
ENUM_SET(KeyCodes, F15, 0x3E),
ENUM_SET(KeyCodes, F16, 0x3F),
ENUM_END
ENUM_TYPE(KeyCodes);

typedef uint16_t key_info[3];
const size_t KI_Normal=0;
const size_t KI_Shift=1;
const size_t KI_AltGr=2;
const uint8_t Keyboard_Flag=0x01;

inline static char KB_char(uint32_t value){
	if((value >> 24) != Keyboard_Flag) return 0;
	uint16_t keycode=(uint16_t)value;
	if(!(keycode & ENUM_GET(KeyFlags, KeyUp)) && !(keycode & ENUM_GET(KeyFlags, NonASCII))) return (char)value;
	else return 0;
}

inline static uint16_t KB_code(uint32_t value){
	if((value >> 24) != Keyboard_Flag) return 0;
	uint16_t keycode=(uint16_t)value;
	return keycode;
}

#endif
