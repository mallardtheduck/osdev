#include "kernel.hpp"

uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}
 
uint16_t make_vgaentry(char c, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}
 
size_t strlen(const char* str)
{
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 24;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize()
{
	dbgout("Terminal init\n");
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
	init_printf(NULL, putc);
}
 
void terminal_scroll(){
	for(size_t y=0; y<VGA_HEIGHT; ++y){
		for(size_t x=0; x<VGA_WIDTH; ++x){
			const size_t source = y * VGA_WIDTH + x;
			if(y){
				const size_t dest = (y-1) * VGA_WIDTH + x;
				terminal_buffer[dest]=terminal_buffer[source];
			}
			terminal_putentryat(' ', terminal_color, x, y);
		}
	}
	terminal_column=0;
	terminal_row=VGA_HEIGHT-1;
	terminal_poscursor(terminal_row, terminal_column);
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}
 
void terminal_putchar(char c)
{
	if(c == '\n'){
		if(++terminal_row >= VGA_HEIGHT){
			terminal_scroll();
		}
		terminal_column = 0;
		return;
	}
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if ( ++terminal_column >= VGA_WIDTH )
	{
		terminal_column = 0;
		if ( ++terminal_row >= VGA_HEIGHT )
		{
			terminal_scroll();
			//terminal_row = 0;
		}
	}
}

void terminal_poscursor(size_t row, size_t col){
    unsigned short position=(row*80) + col;
 
    // cursor LOW port to vga INDEX register
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(position&0xFF));
    // cursor HIGH port to vga INDEX register
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char )((position>>8)&0xFF));
}

void terminal_writestring(const char* data)
{
	size_t datalen = strlen(data);
	for (size_t i = 0; i < datalen; i++) terminal_putchar(data[i]);
	terminal_poscursor(terminal_row, terminal_column);
}

void terminal_writeint(const int i, int base)
{
	char buf[128];
	itoa(i, buf, base);
	terminal_writestring(buf);
}

extern "C" void putc(void*, char c){
	terminal_putchar(c);
	terminal_poscursor(terminal_row, terminal_column);
}
