#include "vga.hpp"

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

#pragma GCC diagnostic ignored "-Wunused-parameter"

void set_mode640x480x4bpp();

extern "C" int module_main(syscall_table *systbl, char *params){
	SYSCALL_TABLE=systbl;
	set_mode640x480x4bpp();
	return 0;
}

uint8_t read_graphics(uint8_t index){
	outb(VGA_Ports::GraphicsAddress, index);
	return inb(VGA_Ports::GraphicsData);
}

void write_graphics(uint8_t index, uint8_t byte){
	outb(VGA_Ports::GraphicsAddress, index);
	outb(VGA_Ports::GraphicsData, byte);
}

uint8_t read_sequencer(uint8_t index){
	outb(VGA_Ports::SequencerAddress, index);
	return inb(VGA_Ports::SequencerData);
}

void write_sequencer(uint8_t index, uint8_t byte){
	outb(VGA_Ports::SequencerAddress, index);
	outb(VGA_Ports::SequencerData, byte);
}

uint8_t read_crtc(uint8_t index){
	outb(VGA_Ports::CRTCAddress, index);
	return inb(VGA_Ports::CRTCData);
}

void write_crtc(uint8_t index, uint8_t byte){
	outb(VGA_Ports::CRTCAddress, index);
	outb(VGA_Ports::CRTCData, byte);
}

uint8_t read_attribute(uint8_t index){
	inb(VGA_Ports::InputStatus1);
	outb(VGA_Ports::AttributeWrite, index);
	return inb(VGA_Ports::AttributeRead);
}

void write_attribute(uint8_t index, uint8_t byte){
	inb(VGA_Ports::InputStatus1);
	outb(VGA_Ports::AttributeWrite, index);
	outb(VGA_Ports::AttributeWrite, byte);
}

void set_mode640x480x4bpp() {
	write_attribute(Attribute_Registers::ModeControl, 0x01);
	write_attribute(Attribute_Registers::OverscanColour, 0x00);
	write_attribute(Attribute_Registers::ColourPlaneEnable, 0x0F);
	write_attribute(Attribute_Registers::PixelPanning, 0x00);
	write_attribute(Attribute_Registers::ColourSelect, 0x00);
	outb(VGA_Ports::MiscOutputWrite, 0xE3);
	write_sequencer(Sequencer_Registers::ClockingMode, 0x01);
	write_sequencer(Sequencer_Registers::CharMapSelect, 0x00);
	write_sequencer(Sequencer_Registers::SeqMemoryMode, 0x02);
	write_graphics(Graphics_Registers::GraphicsMode, 0x00);
	write_graphics(Graphics_Registers::MiscGraphics, 0x05);
	write_crtc(CRTC_Registers::HrzTotal, 0x5F);
	write_crtc(CRTC_Registers::EndHrzDisplay, 0x4F);
	write_crtc(CRTC_Registers::StartHrzBlanking, 0x50);
	write_crtc(CRTC_Registers::EndHrzBlanking, 0x82);
	write_crtc(CRTC_Registers::StartHrzRetrace, 0x54);
	write_crtc(CRTC_Registers::EndHrzRetrace, 0x80);
	write_crtc(CRTC_Registers::VrtTotal, 0x0B);
	write_crtc(CRTC_Registers::Overflow, 0x3E);
	write_crtc(CRTC_Registers::PresetRowScan, 0x00);
	write_crtc(CRTC_Registers::MaxScanLine, 0x40);
	write_crtc(CRTC_Registers::StartVrtRetrace, 0xEA);
	write_crtc(CRTC_Registers::EndVrtRetrace, 0x8C);
	write_crtc(CRTC_Registers::EndVrtDisplay, 0xDF);
	write_crtc(CRTC_Registers::Offset, 0x28);
	write_crtc(CRTC_Registers::UnderlineLoc, 0x00);
	write_crtc(CRTC_Registers::StartVrtBlanking, 0xE7);
	write_crtc(CRTC_Registers::EndHrzBlanking, 0x04);
	write_crtc(CRTC_Registers::CRTCModeControl, 0xE3);
}