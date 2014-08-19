#include "kernel.hpp"

#pragma GCC diagnostic ignored "-Wunused-parameter"

namespace instance_mode{
	enum Enum{
		Simple,
		Raw,
	};
};

struct terminal_instance{
	size_t pos;
	instance_mode::Enum mode;
};

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static const size_t max=VGA_WIDTH * VGA_HEIGHT * 2;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void *terminal_open(void*){
	terminal_instance *inst = new terminal_instance();
	inst->pos=0;
	inst->mode=instance_mode::Simple;
	return (void*) inst;
}

bool terminal_close(void *inst){
	free(inst);
	return true;
}

size_t terminal_read(void *instance, size_t bytes, char *buf){
	terminal_instance *inst=(terminal_instance*)instance;
	if(inst->pos > max) return 0;
	if(inst->pos+bytes > max) bytes=max-inst->pos;
	memcpy(buf, (char*)terminal_buffer+inst->pos, bytes);
	inst->pos+=bytes;
	return bytes;
}

size_t terminal_write(void *instance, size_t bytes, char *buf){
	terminal_instance *inst=(terminal_instance*)instance;
	if(inst->mode==instance_mode::Raw){
		if(inst->pos > max) return 0;
        if(inst->pos+bytes > max) bytes=max-inst->pos;
		memcpy((char*)terminal_buffer+inst->pos, buf, bytes);
		inst->pos+=bytes;
		return bytes;
	}else{
	    char *obuf=(char*)malloc(bytes+1);
	    memset(obuf, 0, bytes+1);
	    memcpy(obuf, buf, bytes);
		terminal_writestring(obuf);
		free(obuf);
		return bytes;
	}
}

size_t terminal_seek(void *instance, size_t pos, bool relative){
	terminal_instance *inst=(terminal_instance*)instance;
	size_t ret=0;
	if(inst->mode==instance_mode::Raw){
		//TODO: Bounds checking!
		if(relative) inst->pos+=pos;
		else inst->pos=pos;
		ret=inst->pos;
	}else{
		size_t cpos;
		if(relative){
			cpos=(terminal_row * VGA_WIDTH) + terminal_column;
			cpos+=pos;
		}else{
			cpos=pos;
		}
		if(cpos > VGA_HEIGHT * VGA_WIDTH){
			dbgpf("Bad terminal seek: %i\n", cpos);
			cpos=VGA_HEIGHT * VGA_WIDTH;
		}
		terminal_row=cpos/VGA_WIDTH;
		terminal_column=cpos-(terminal_row * VGA_WIDTH);
		terminal_poscursor(terminal_row, terminal_column);
		ret=cpos;
	}
	return ret;
}

int terminal_ioctl(void *instance, int fn, size_t bytes, char *buf){
	//TODO: Stuff...
	return 0;
}

int terminal_type(){
	return driver_types::VID_TEXT;
}

char *terminal_desc(){
	return "Basic VGA text output.";
}

/*struct drv_driver{
	void *(*open)();
	bool (*close)(void *instance);
	int (*read)(void *instance, size_t bytes, char *buf);
	bool (*write)(void *instance, size_t bytes, char *buf);
	void (*seek)(void *instance, size_t pos, bool relative);
	int (*ioctl)(void *instance, int fn, size_t bytes, char *buf);
	int (*type)();
	char *(*desc)();
};*/

drv_driver terminal_driver={terminal_open, terminal_close, terminal_read, terminal_write, terminal_seek,
				terminal_ioctl, terminal_type, terminal_desc};

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

void terminal_add_device(){
	char name[12]={"VGATEXT\0"};
	drv_add_device(name, &terminal_driver, NULL);
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
	}else if(c == '\t'){
		terminal_column = (terminal_column + 8) & ~7;
		if(terminal_column>=VGA_WIDTH){
			terminal_scroll();
			terminal_column = 0;
		}
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

void terminal_move(int x, int y){
	terminal_row=y;
	terminal_column=x;
	terminal_poscursor(terminal_row, terminal_column);
}

extern "C" void putc(void*, char c){
	terminal_putchar(c);
	terminal_poscursor(terminal_row, terminal_column);
}

