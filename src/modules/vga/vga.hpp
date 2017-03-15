#ifndef	_VGA_HPP
#define _VGA_HPP

#include <btos_module.h>

extern volatile uint8_t * const vga_memory;
extern volatile uint8_t * const text_memory;

namespace VGA_Ports{
	static const uint16_t GraphicsAddress 	=0x3CE;
	static const uint16_t GraphicsData		=0x3CF;
	static const uint16_t SequencerAddress	=0x3C4;
	static const uint16_t SequencerData		=0x3C5;
	static const uint16_t AttributeWrite	=0x3C0;
	static const uint16_t AttributeRead		=0x3C1;
	static const uint16_t CRTCAddress		=0x3D4;
	static const uint16_t CRTCData			=0x3D5;
	static const uint16_t DACReadAddress	=0x3C7;
	static const uint16_t DACWriteAddress	=0x3C8;
	static const uint16_t DACData			=0x3C9;
	static const uint16_t DACState			=0x3C7;
	static const uint16_t MiscOutputRead	=0x3CC;
	static const uint16_t MiscOutputWrite	=0x3C2;
	static const uint16_t FeatureCtrlRead	=0x3CA;
	static const uint16_t FeatureCtrlWrite	=0x3DA;
	static const uint16_t InputStatus0		=0x3C2;
	static const uint16_t InputStatus1		=0x3DA;
}

namespace Graphics_Registers{
	static const uint8_t SetReset			=0x00;
	static const uint8_t EnableSetReset		=0x01;
	static const uint8_t ColourCompare		=0x02;
	static const uint8_t DataRotate			=0x03;
	static const uint8_t ReadMapSelect		=0x04;
	static const uint8_t GraphicsMode		=0x05;
	static const uint8_t MiscGraphics		=0x06;
	static const uint8_t ColourDontCare		=0x07;
	static const uint8_t BitMask			=0x08;
}

namespace Sequencer_Registers{
	static const uint8_t Reset				=0x00;
	static const uint8_t ClockingMode		=0x01;
	static const uint8_t MapMask			=0x02;
	static const uint8_t CharMapSelect		=0x03;
	static const uint8_t SeqMemoryMode		=0x04;
}

namespace Attribute_Registers{
	static const uint8_t Palette0			=0x00;
	static const uint8_t Palette1			=0x01;
	static const uint8_t Palette2			=0x02;
	static const uint8_t Palette3			=0x03;
	static const uint8_t Palette4			=0x04;
	static const uint8_t Palette5			=0x05;
	static const uint8_t Palette6			=0x06;
	static const uint8_t Palette7			=0x07;
	static const uint8_t Palette8			=0x08;
	static const uint8_t Palette9			=0x09;
	static const uint8_t PaletteA			=0x0A;
	static const uint8_t PaletteB			=0x0B;
	static const uint8_t PaletteC			=0x0C;
	static const uint8_t PaletteD			=0x0D;
	static const uint8_t PaletteE			=0x0E;
	static const uint8_t PaletteF			=0x0F;
	static const uint8_t ModeControl		=0x10;
	static const uint8_t OverscanColour		=0x11;
	static const uint8_t ColourPlaneEnable	=0x12;
	static const uint8_t PixelPanning		=0x13;
	static const uint8_t ColourSelect		=0x14;
}

namespace CRTC_Registers{
	static const uint8_t HrzTotal			=0x00;
	static const uint8_t EndHrzDisplay		=0x01;
	static const uint8_t StartHrzBlanking	=0x02;
	static const uint8_t EndHrzBlanking		=0x03;
	static const uint8_t StartHrzRetrace	=0x04;
	static const uint8_t EndHrzRetrace		=0x05;
	static const uint8_t VrtTotal			=0x06;
	static const uint8_t Overflow			=0x07;
	static const uint8_t PresetRowScan		=0x08;
	static const uint8_t MaxScanLine		=0x09;
	static const uint8_t CursorStart		=0x0A;
	static const uint8_t CursorEnd			=0x0B;
	static const uint8_t StartAddrHigh		=0x0C;
	static const uint8_t StartAddrLow		=0x0D;
	static const uint8_t CursorLocHigh		=0x0E;
	static const uint8_t CursorLocLow		=0x0F;
	static const uint8_t StartVrtRetrace	=0x10;
	static const uint8_t EndVrtRetrace		=0x11;
	static const uint8_t EndVrtDisplay		=0x12;
	static const uint8_t Offset				=0x13;
	static const uint8_t UnderlineLoc		=0x14;
	static const uint8_t StartVrtBlanking	=0x15;
	static const uint8_t EndVrtBlanking		=0x16;
	static const uint8_t CRTCModeControl	=0x17;
	static const uint8_t LineCompare		=0x18;
}

uint8_t read_graphics(uint8_t index);
void write_graphics(uint8_t index, uint8_t byte);
uint8_t read_sequencer(uint8_t index);
void write_sequencer(uint8_t index, uint8_t byte);
uint8_t read_crtc(uint8_t index);
void write_crtc(uint8_t index, uint8_t byte);
uint8_t read_attribute(uint8_t index);
void write_attribute(uint8_t index, uint8_t byte);
void write_dac(uint8_t index, uint8_t r, uint8_t g, uint8_t b);
void read_dac(uint8_t index, uint8_t &r, uint8_t &g, uint8_t &b);

static const size_t vga_font_size=(16*256);

void unlock_crtc();
void lock_crtc();
void disable_display();
void enable_display();
void dump_regs();

#endif