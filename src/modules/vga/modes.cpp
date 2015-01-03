#include "modes.hpp"

void select_plane(uint8_t plane) {
	write_sequencer(Sequencer_Registers::MapMask, 1 << plane);
	write_graphics(Graphics_Registers::ReadMapSelect, plane);
}

void set_mode_12h() {
	disable_interrupts();
	disable_display();
	unlock_crtc();
	outb(VGA_Ports::MiscOutputWrite, 0xE3);
	write_sequencer(Sequencer_Registers::Reset, 0x03);
	write_sequencer(Sequencer_Registers::ClockingMode, 0x21);
	write_sequencer(Sequencer_Registers::MapMask, 0x08);
	write_sequencer(Sequencer_Registers::CharMapSelect, 0x00);
	write_sequencer(Sequencer_Registers::SeqMemoryMode, 0x06);
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
	write_crtc(CRTC_Registers::CursorStart, 0x00);
	write_crtc(CRTC_Registers::CursorEnd, 0x00);
	write_crtc(CRTC_Registers::StartAddrHigh, 0x00);
	write_crtc(CRTC_Registers::StartAddrLow, 0x00);
	write_crtc(CRTC_Registers::CursorLocHigh, 0x00);
	write_crtc(CRTC_Registers::CursorLocLow, 0x00);
	write_crtc(CRTC_Registers::StartVrtRetrace, 0xEA);
	write_crtc(CRTC_Registers::EndVrtRetrace, 0x8C);
	write_crtc(CRTC_Registers::EndVrtDisplay, 0xDF);
	write_crtc(CRTC_Registers::Offset, 0x28);
	write_crtc(CRTC_Registers::UnderlineLoc, 0x00);
	write_crtc(CRTC_Registers::StartVrtBlanking, 0xE7);
	write_crtc(CRTC_Registers::EndVrtBlanking, 0x04);
	write_crtc(CRTC_Registers::CRTCModeControl, 0xE3);
	write_crtc(CRTC_Registers::LineCompare, 0xFF);
	write_graphics(Graphics_Registers::SetReset, 0x00);
	write_graphics(Graphics_Registers::EnableSetReset, 0x00);
	write_graphics(Graphics_Registers::ColourCompare, 0x00);
	write_graphics(Graphics_Registers::DataRotate, 0x00);
	write_graphics(Graphics_Registers::ReadMapSelect, 0x03);
	write_graphics(Graphics_Registers::GraphicsMode, 0x00);
	write_graphics(Graphics_Registers::MiscGraphics, 0x05);
	write_graphics(Graphics_Registers::ColourDontCare, 0x0F);
	write_graphics(Graphics_Registers::BitMask, 0xFF);
	write_attribute(Attribute_Registers::ModeControl, 0x01);
	write_attribute(Attribute_Registers::OverscanColour, 0x00);
	write_attribute(Attribute_Registers::ColourPlaneEnable, 0x0F);
	write_attribute(Attribute_Registers::PixelPanning, 0x00);
	write_attribute(Attribute_Registers::ColourSelect, 0x00);
	inb(VGA_Ports::InputStatus1);
	outb(VGA_Ports::AttributeWrite, 0x20);
	lock_crtc();
	for(uint8_t i=0; i<4; ++i){
		select_plane(i);
		memset((void*)vga_memory, 0x00, 64*1024);
	}
	enable_display();
	enable_interrupts();
}

void put_pixel_12h(uint32_t x, uint32_t y, uint8_t value){
	uint16_t byte = ((y * 640) + x) >> 3;
	uint8_t bit = (x & 0x07);
	uint8_t mask=(1 << bit);
	for(int i=0; i<4; ++i){
		bool set=value & (1 << i);
		select_plane(i);
		uint8_t cbyte=vga_memory[byte];
		if(set){
			cbyte |= mask;
		}else{
			cbyte &= ~mask;
		}
		vga_memory[byte]=cbyte;
	}
}

uint8_t get_pixel_12h(uint32_t x, uint32_t y){
	uint16_t byte = ((y * 640) + x) >> 3;
	uint8_t bit = (x & 0x07);
	uint8_t mask=(1 << bit);
	uint8_t ret=0;
	for(int i=0; i<4; ++i){
		select_plane(i);
		uint8_t cbyte=vga_memory[byte];
		if(cbyte & mask){
			ret |= (1 << i);
		}else{
			ret &= ~(1 << i);
		}
	}
	return ret;
}

void test_mode(){
	set_mode_12h();
	put_pixel_12h(50, 50, 1);
	for(int x=0; x<640; ++x){
		put_pixel_12h(x, 100, 2);
	}
	for(int y=0; y<480; ++y){
		put_pixel_12h(100, y, 4);
	}
	dbgpf("VGA: Pixel at (50, 50): %x\n", (int)get_pixel_12h(50, 50));
	while(true) asm volatile("hlt");
}

vga_mode vga_modes[]= {
		{{0x12, 640, 480, 4, false, false}, &set_mode_12h, &put_pixel_12h, &get_pixel_12h}
};