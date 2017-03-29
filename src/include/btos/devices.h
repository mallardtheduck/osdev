#ifndef _DEVICES_H
#define _DEVICES_H

#ifdef __cplusplus
namespace driver_types{
#endif
	static const int TIMER		= 0x01;
	static const int BUS		= 0x02;
	static const int INPUT		= 0x10;
	static const int IN_KEYBOARD 	= 0x11;
	static const int IN_MOUSE	= 0x12;
	static const int IN_GAME	= 0x13;
	static const int IN_TOUCH	= 0x14;
	static const int IN_TABLET = 0x15;
	static const int VIDEO		= 0x20;
	static const int VID_TEXT	= 0x21;
	static const int STORAGE	= 0x30;
	static const int STR_HDD	= 0x31;
	static const int STR_OPTICAL	= 0x32;
	static const int STR_SSD	= 0x33;
	static const int STR_FLASH	= 0x34;
	static const int STR_MEMCARD	= 0x35;
	static const int STR_FLOPPY = 0x35;
	static const int STR_TAPE	 = 0x36;
	static const int STR_PART	= 0x37;
	static const int NIC		= 0x40;
	static const int NIC_ETHERNET	= 0x41;
	static const int NIC_WIRELESS	= 0x42;
	static const int AUDIO		= 0x50;
	static const int AUD_OUTPUT	= 0x51;
	static const int AUD_INPUT	= 0x52;
	static const int IOPORT	= 0x60;
	static const int IO_SERIAL	= 0x61;
	static const int IO_PARALELL	= 0x62;
	static const int IO_BLUETOOTH	= 0x63;
	static const int PRINTER	= 0x70;
	static const int PRN_TEXT	= 0x71;
	static const int GRAPHICINPUT	= 0x80;
	static const int GI_SCANNER	= 0x81;
	static const int GI_STILLCAM	= 0x82;
	static const int GI_VIDCAM	= 0x83;
	static const int LCDSCREEN	= 0x90;
    static const int TERMINAL   = 0xA0;
	static const int BESPOKE	= 0xF0;
	static const int USER		= 0xFF;
#ifdef __cplusplus
};
#endif

#endif