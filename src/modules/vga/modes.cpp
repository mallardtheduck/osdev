#include "modes.hpp"
#include "ops.hpp"

extern uint8_t vga_font[vga_font_size];
extern vga_palette_entry vga_palette[256];

void select_plane(uint8_t plane) {
	write_sequencer(Sequencer_Registers::MapMask, (uint8_t)1 << plane);
	write_graphics(Graphics_Registers::ReadMapSelect, plane);
}

void load_palette() {
	for(int i=0; i<256; ++i){
		vga_palette_entry entry=vga_palette[i];
		write_dac(i, entry.r, entry.g, entry.b);
	}
}

void load_font(){
	write_graphics(Graphics_Registers::MiscGraphics, 0x04);
	write_sequencer(Sequencer_Registers::SeqMemoryMode, 0x06);
	write_graphics(Graphics_Registers::GraphicsMode, 0x00);
	select_plane(2);
	for(int i=0; i<256; ++i){
		int srcidx=i*16;
		int dstidx=i*32;
		dbgpf("VGA: Copy character from %p to %p.\n", &vga_font[dstidx], &vga_memory[dstidx]);
		memset((void*)&vga_memory[dstidx], 0, 32);
		memcpy((void*)&vga_memory[dstidx], &vga_font[srcidx], 16);
	}
	select_plane(0);
	write_graphics(Graphics_Registers::GraphicsMode, 0x10);
	write_sequencer(Sequencer_Registers::MapMask, 0x03);
	write_sequencer(Sequencer_Registers::SeqMemoryMode, 0x02);
	write_graphics(Graphics_Registers::MiscGraphics, 0x0E);
}

void set_mode_12h() {
	disable_interrupts();
	disable_display();
	unlock_crtc();
	outb(VGA_Ports::MiscOutputWrite, 0xE3);
	write_sequencer(Sequencer_Registers::Reset, 0x03);
	write_sequencer(Sequencer_Registers::ClockingMode, 0x01);
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
	write_attribute(Attribute_Registers::Palette0, 0x00);
	write_attribute(Attribute_Registers::Palette1, 0x01);
	write_attribute(Attribute_Registers::Palette2, 0x02);
	write_attribute(Attribute_Registers::Palette3, 0x03);
	write_attribute(Attribute_Registers::Palette4, 0x04);
	write_attribute(Attribute_Registers::Palette5, 0x05);
	write_attribute(Attribute_Registers::Palette6, 0x06);
	write_attribute(Attribute_Registers::Palette7, 0x07);
	write_attribute(Attribute_Registers::Palette8, 0x08);
	write_attribute(Attribute_Registers::Palette9, 0x09);
	write_attribute(Attribute_Registers::PaletteA, 0x0A);
	write_attribute(Attribute_Registers::PaletteB, 0x0B);
	write_attribute(Attribute_Registers::PaletteC, 0x0C);
	write_attribute(Attribute_Registers::PaletteD, 0x0D);
	write_attribute(Attribute_Registers::PaletteE, 0x0E);
	write_attribute(Attribute_Registers::PaletteF, 0x0F);
	write_attribute(Attribute_Registers::ModeControl, 0x01);
	write_attribute(Attribute_Registers::OverscanColour, 0x00);
	write_attribute(Attribute_Registers::ColourPlaneEnable, 0x0F);
	write_attribute(Attribute_Registers::PixelPanning, 0x00);
	write_attribute(Attribute_Registers::ColourSelect, 0x00);
	inb(VGA_Ports::InputStatus1);
	outb(VGA_Ports::AttributeWrite, 0x20);
	lock_crtc();
	load_palette();
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

static uint8_t smallbuffer[1024];

inline uint8_t *get_copybuffer(size_t size){
	if(size <= 1024) return smallbuffer;
	else return (uint8_t*)malloc(size);
}

inline void free_copybuffer(uint8_t *ptr){
	if(ptr != smallbuffer) free(ptr);
}

void write_pixels_12h(uint32_t startpos, size_t count, uint8_t *data){
	uint32_t startbyte=startpos / 8;
	uint8_t sbits=(uint8_t)(startpos-(startbyte * 8));
	count += sbits;
	uint32_t bytes=(uint32_t)(count / 8);
	if(bytes * 8 < count) bytes++;
	uint8_t xbits = (bytes * 8) - count;
	for(uint8_t plane=0; plane<4; ++plane) {
		uint8_t skipbits=sbits;
		uint8_t goodbits=8 - xbits;
		select_plane(plane);
		uint32_t pixpos=startpos;
		uint8_t *copybuffer = get_copybuffer(bytes);
		for(size_t byte=startbyte; byte<startbyte+bytes; ++byte){
			uint8_t cbyte=0;
			if(byte==startbyte || byte==startbyte+bytes-1) cbyte=vga_memory[byte];
			for(uint8_t bit=0; bit < 8; ++bit){
				if(skipbits){
					skipbits--;
					continue;
				}
				if(byte==startbyte+bytes-1){
					if(goodbits) goodbits--;
					else break;
				}
				if(pixpos-startpos >= count) break;
				size_t index=(pixpos-startpos)/2;
				uint8_t dbyte;
				if((pixpos-startpos) % 2){
					dbyte=(uint8_t)(data[index] & 0x0F);
				}else{
					dbyte=(uint8_t)((data[index] >> 4) & 0x0F);
				}
				bool dbit=!!(dbyte & (1 << plane));
				if(dbit){
					cbyte |= (1 << (7-bit));
				}else{
					cbyte &= ~(1 << (7-bit));
				}
				pixpos++;
			}
			//vga_memory[byte]=cbyte;
			copybuffer[byte - startbyte] = cbyte;
		}
		memcpy((void*)(vga_memory + startbyte), copybuffer, bytes);
		free_copybuffer(copybuffer);
	}
}

void read_pixels_12h(uint32_t startpos, size_t count, uint8_t *data){
	uint32_t startbyte=startpos / 8;
	uint8_t sbits=(uint8_t)(startpos-(startbyte * 8));
	count += sbits;
	uint32_t bytes=(uint32_t)(count / 8);
	if(bytes * 8 < count) bytes++;
	uint8_t xbits = (bytes * 8) - count;
	for(uint8_t plane=0; plane<4; ++plane) {
		uint8_t skipbits=sbits;
		uint8_t goodbits=8 - xbits;
		select_plane(plane);
		uint32_t pixpos=startpos;
		for(size_t byte=startbyte; byte<startbyte+bytes; ++byte){
			uint8_t cbyte=vga_memory[byte];
			for(uint8_t bit=0; bit < 8; ++bit){
				if(skipbits){
					skipbits--;
					continue;
				}
				if(byte==startbyte+bytes-1){
					if(goodbits) goodbits--;
					else break;
				}
				if(pixpos-startpos >= count) break;
				size_t index=(pixpos-startpos)/2;
				uint8_t dbyte;
				if((pixpos-startpos) % 2){
					dbyte=(uint8_t)(data[index] & 0x0F);
				}else{
					dbyte=(uint8_t)((data[index] >> 4) & 0x0F);
				}
				bool cbit=!!(cbyte & (1 << (7-bit)));
				if(cbit){
					dbyte |= (1 << plane);
				}else{
					dbyte &= ~(1 << plane);
				}
				if((pixpos-startpos) % 2){
					data[index] = (uint8_t)((data[index] & 0xF0) | (dbyte & 0x0F));
				}else{
					data[index] = (uint8_t)((data[index] & 0x0F) | ((dbyte << 4) & 0xF0));
				}
				pixpos++;
			}
		}
	}
}

void set_mode_03h() {
	disable_interrupts();
	disable_display();
	unlock_crtc();
	outb(VGA_Ports::MiscOutputWrite, 0x67);
	write_sequencer(Sequencer_Registers::Reset, 0x03);
	write_sequencer(Sequencer_Registers::ClockingMode, 0x00);
	write_sequencer(Sequencer_Registers::MapMask, 0x03);
	write_sequencer(Sequencer_Registers::CharMapSelect, 0x00);
	write_sequencer(Sequencer_Registers::SeqMemoryMode, 0x02);
	write_crtc(CRTC_Registers::HrzTotal, 0x5F);
	write_crtc(CRTC_Registers::EndHrzDisplay, 0x4F);
	write_crtc(CRTC_Registers::StartHrzBlanking, 0x50);
	write_crtc(CRTC_Registers::EndHrzBlanking, 0x82);
	write_crtc(CRTC_Registers::StartHrzRetrace, 0x55);
	write_crtc(CRTC_Registers::EndHrzRetrace, 0x81);
	write_crtc(CRTC_Registers::VrtTotal, 0xBF);
	write_crtc(CRTC_Registers::Overflow, 0x1F);
	write_crtc(CRTC_Registers::PresetRowScan, 0x00);
	write_crtc(CRTC_Registers::MaxScanLine, 0x4F);
	write_crtc(CRTC_Registers::CursorStart, 0x0D);
	write_crtc(CRTC_Registers::CursorEnd, 0x0E);
	write_crtc(CRTC_Registers::StartAddrHigh, 0x00);
	write_crtc(CRTC_Registers::StartAddrLow, 0x00);
	write_crtc(CRTC_Registers::CursorLocHigh, 0x00);
	write_crtc(CRTC_Registers::CursorLocLow, 0x50);
	write_crtc(CRTC_Registers::StartVrtRetrace, 0x9C);
	write_crtc(CRTC_Registers::EndVrtRetrace, 0x8E);
	write_crtc(CRTC_Registers::EndVrtDisplay, 0x8F);
	write_crtc(CRTC_Registers::Offset, 0x28);
	write_crtc(CRTC_Registers::UnderlineLoc, 0x1F);
	write_crtc(CRTC_Registers::StartVrtBlanking, 0x96);
	write_crtc(CRTC_Registers::EndVrtBlanking, 0xB9);
	write_crtc(CRTC_Registers::CRTCModeControl, 0xA3);
	write_crtc(CRTC_Registers::LineCompare, 0xFF);
	write_graphics(Graphics_Registers::SetReset, 0x00);
	write_graphics(Graphics_Registers::EnableSetReset, 0x00);
	write_graphics(Graphics_Registers::ColourCompare, 0x00);
	write_graphics(Graphics_Registers::DataRotate, 0x00);
	write_graphics(Graphics_Registers::ReadMapSelect, 0x00);
	write_graphics(Graphics_Registers::GraphicsMode, 0x10);
	write_graphics(Graphics_Registers::MiscGraphics, 0x0E);
	write_graphics(Graphics_Registers::ColourDontCare, 0x00);
	write_graphics(Graphics_Registers::BitMask, 0xFF);
	write_attribute(Attribute_Registers::Palette0, 0x00);
	write_attribute(Attribute_Registers::Palette1, 0x01);
	write_attribute(Attribute_Registers::Palette2, 0x02);
	write_attribute(Attribute_Registers::Palette3, 0x03);
	write_attribute(Attribute_Registers::Palette4, 0x04);
	write_attribute(Attribute_Registers::Palette5, 0x05);
	write_attribute(Attribute_Registers::Palette6, 0x06);
	write_attribute(Attribute_Registers::Palette7, 0x07);
	write_attribute(Attribute_Registers::Palette8, 0x08);
	write_attribute(Attribute_Registers::Palette9, 0x09);
	write_attribute(Attribute_Registers::PaletteA, 0x0A);
	write_attribute(Attribute_Registers::PaletteB, 0x0B);
	write_attribute(Attribute_Registers::PaletteC, 0x0C);
	write_attribute(Attribute_Registers::PaletteD, 0x0D);
	write_attribute(Attribute_Registers::PaletteE, 0x0E);
	write_attribute(Attribute_Registers::PaletteF, 0x0F);
	write_attribute(Attribute_Registers::ModeControl, 0x0C);
	write_attribute(Attribute_Registers::OverscanColour, 0x00);
	write_attribute(Attribute_Registers::ColourPlaneEnable, 0x0F);
	write_attribute(Attribute_Registers::PixelPanning, 0x08);
	write_attribute(Attribute_Registers::ColourSelect, 0x00);
	inb(VGA_Ports::InputStatus1);
	outb(VGA_Ports::AttributeWrite, 0x20);
	lock_crtc();
	load_palette();
	load_font();
	enable_display();
	enable_interrupts();
	init_text();
}

void set_mode_x() {
	disable_interrupts();
	disable_display();
	unlock_crtc();
	outb(VGA_Ports::MiscOutputWrite, 0xE3);
	write_sequencer(Sequencer_Registers::Reset, 0x03);
	write_sequencer(Sequencer_Registers::ClockingMode, 0x01);
	write_sequencer(Sequencer_Registers::MapMask, 0x0F);
	write_sequencer(Sequencer_Registers::CharMapSelect, 0x00);
	write_sequencer(Sequencer_Registers::SeqMemoryMode, 0x06);
	write_crtc(CRTC_Registers::HrzTotal, 0x5F);
	write_crtc(CRTC_Registers::EndHrzDisplay, 0x4F);
	write_crtc(CRTC_Registers::StartHrzBlanking, 0x50);
	write_crtc(CRTC_Registers::EndHrzBlanking, 0x82);
	write_crtc(CRTC_Registers::StartHrzRetrace, 0x54);
	write_crtc(CRTC_Registers::EndHrzRetrace, 0x80);
	write_crtc(CRTC_Registers::VrtTotal, 0x0D);
	write_crtc(CRTC_Registers::Overflow, 0x3E);
	write_crtc(CRTC_Registers::PresetRowScan, 0x00);
	write_crtc(CRTC_Registers::MaxScanLine, 0x41);
	write_crtc(CRTC_Registers::CursorStart, 0x00);
	write_crtc(CRTC_Registers::CursorEnd, 0x00);
	write_crtc(CRTC_Registers::StartAddrHigh, 0x00);
	write_crtc(CRTC_Registers::StartAddrLow, 0x00);
	write_crtc(CRTC_Registers::CursorLocHigh, 0x00);
	write_crtc(CRTC_Registers::CursorLocLow, 0x00);
	write_crtc(CRTC_Registers::StartVrtRetrace, 0xEA);
	write_crtc(CRTC_Registers::EndVrtRetrace, 0xAC);
	write_crtc(CRTC_Registers::EndVrtDisplay, 0xDF);
	write_crtc(CRTC_Registers::Offset, 0x28);
	write_crtc(CRTC_Registers::UnderlineLoc, 0x00);
	write_crtc(CRTC_Registers::StartVrtBlanking, 0xE7);
	write_crtc(CRTC_Registers::EndVrtBlanking, 0x06);
	write_crtc(CRTC_Registers::CRTCModeControl, 0xE3);
	write_crtc(CRTC_Registers::LineCompare, 0xFF);
	write_graphics(Graphics_Registers::SetReset, 0x00);
	write_graphics(Graphics_Registers::EnableSetReset, 0x00);
	write_graphics(Graphics_Registers::ColourCompare, 0x00);
	write_graphics(Graphics_Registers::DataRotate, 0x00);
	write_graphics(Graphics_Registers::ReadMapSelect, 0x00);
	write_graphics(Graphics_Registers::GraphicsMode, 0x40);
	write_graphics(Graphics_Registers::MiscGraphics, 0x05);
	write_graphics(Graphics_Registers::ColourDontCare, 0x0F);
	write_graphics(Graphics_Registers::BitMask, 0xFF);
	write_attribute(Attribute_Registers::Palette0, 0x00);
	write_attribute(Attribute_Registers::Palette1, 0x01);
	write_attribute(Attribute_Registers::Palette2, 0x02);
	write_attribute(Attribute_Registers::Palette3, 0x03);
	write_attribute(Attribute_Registers::Palette4, 0x04);
	write_attribute(Attribute_Registers::Palette5, 0x05);
	write_attribute(Attribute_Registers::Palette6, 0x06);
	write_attribute(Attribute_Registers::Palette7, 0x07);
	write_attribute(Attribute_Registers::Palette8, 0x08);
	write_attribute(Attribute_Registers::Palette9, 0x09);
	write_attribute(Attribute_Registers::PaletteA, 0x0A);
	write_attribute(Attribute_Registers::PaletteB, 0x0B);
	write_attribute(Attribute_Registers::PaletteC, 0x0C);
	write_attribute(Attribute_Registers::PaletteD, 0x0D);
	write_attribute(Attribute_Registers::PaletteE, 0x0E);
	write_attribute(Attribute_Registers::PaletteF, 0x0F);
	write_attribute(Attribute_Registers::ModeControl, 0x41);
	write_attribute(Attribute_Registers::OverscanColour, 0x00);
	write_attribute(Attribute_Registers::ColourPlaneEnable, 0x0F);
	write_attribute(Attribute_Registers::PixelPanning, 0x00);
	write_attribute(Attribute_Registers::ColourSelect, 0x00);
	inb(VGA_Ports::InputStatus1);
	outb(VGA_Ports::AttributeWrite, 0x20);
	lock_crtc();
	load_palette();
	for(uint8_t i=0; i<4; ++i){
		select_plane(i);
		memset((void*)vga_memory, 0x00, 64*1024);
	}
	enable_display();
	enable_interrupts();
}

void put_pixel_x(uint32_t x, uint32_t y, uint8_t value){
	uint16_t byte=((y * 320) + x) / 4;
	uint8_t plane=x & 0x03;
	select_plane(plane);
	vga_memory[byte]=value;
}

uint8_t get_pixel_x(uint32_t x, uint32_t y){
	uint16_t byte=((y * 320) + x) / 4;
	uint8_t plane=x & 0x03;
	select_plane(plane);
	return vga_memory[byte];
}

void write_pixels_x(uint32_t startpos, size_t count, uint8_t *data){
	uint32_t rstartpos=startpos & ~0x03;
	uint32_t skip=startpos-rstartpos;
	for(uint8_t plane=0; plane<4; ++plane) {
		if(skip){
			skip--;
			continue;
		}
		size_t pstartpos=rstartpos+plane;
		select_plane(plane);
		for (size_t i = pstartpos; i < startpos + count; i+=4) {
			uint32_t y = (uint32_t) (i / 320);
			uint32_t x = (uint32_t) (i - (320 * y));
			uint16_t byte=((y * 320) + x) / 4;
			vga_memory[byte]=data[i-startpos];
		}
	}
}

void read_pixels_x(uint32_t startpos, size_t count, uint8_t *data){
	uint32_t rstartpos=startpos & ~0x03;
	uint32_t skip=startpos-rstartpos;
	for(size_t plane=0; plane<4; ++plane) {
		if(skip){
			skip--;
			continue;
		}
		size_t pstartpos=rstartpos+plane;
		select_plane(plane);
		for (size_t i = pstartpos; i < startpos + count; i+=4) {
			uint32_t y = (uint32_t) (i / 320);
			uint32_t x = (uint32_t) (i - (320 * y));
			uint16_t byte=((y * 320) + x) / 4;
			data[i-startpos]=vga_memory[byte];
		}
	}
}

vga_mode mode_12h={{0x12, 640, 480, 4, false, false}, &set_mode_12h, &put_pixel_12h, &get_pixel_12h, &write_pixels_12h, &read_pixels_12h};
vga_mode mode_x={{0x58, 320, 240, 8, false, false}, &set_mode_x, &put_pixel_x, &get_pixel_x, &write_pixels_x, &read_pixels_x};
vga_mode mode_03h={{0x03, 80, 25, 4, true, false}, &set_mode_03h, NULL, NULL, NULL, NULL};

vga_mode *vga_modes[]= {&mode_03h, &mode_12h, &mode_x};
const size_t vga_mode_count=3;

vga_mode *current_mode;

void init_modes(){
	current_mode=&mode_03h;
	set_mode_03h();
}