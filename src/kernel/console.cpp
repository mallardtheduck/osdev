#include "kernel.hpp"
#include <dev/video_dev.h>

#pragma GCC diagnostic ignored "-Wunused-parameter"

struct terminal_instance{
	size_t pos;
	bt_vid_text_access_mode::Enum mode;
};

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static const size_t maxchar=VGA_WIDTH * VGA_HEIGHT * 2;

static bt_vidmode mode={
	.id = 0,
	.width = 80,
	.height = 25,
	.bpp = 4,
	.textmode = true,
	.palette = false,
	.bytesPerLine = 160,
	.rBits = 0,
	.rPos = 0,
	.gBits = 0,
	.gPos = 0,
	.bBits = 0,
	.bPos = 0,
};

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
static bool scrolling_enabled=true;

template<typename T> static T max(T a, T b){ return (a>b)?a:b; }

void *terminal_open(void*){
	terminal_instance *inst = new terminal_instance();
	inst->pos=0;
	inst->mode=bt_vid_text_access_mode::Simple;
	return (void*) inst;
}

bool terminal_close(void *inst){
	free(inst);
	return true;
}

size_t terminal_read(void *instance, size_t bytes, char *buf){
	terminal_instance *inst=(terminal_instance*)instance;
    if(inst->mode==bt_vid_text_access_mode::Raw){
	    if(inst->pos > maxchar) return 0;
	    if(inst->pos+bytes > maxchar) bytes=maxchar-inst->pos;
	    memcpy(buf, (char*)terminal_buffer+inst->pos, bytes);
        inst->pos+=bytes;
    }else{
        size_t chars=maxchar/2;
        if(inst->pos > chars) return 0;
        if(inst->pos+bytes > chars) bytes=chars-inst->pos;
        for(size_t i=0; i<bytes; ++i){
            buf[i]=terminal_buffer[inst->pos+i] & 0xFF;
        }
        inst->pos+=bytes;
    }
    return bytes;
}

size_t terminal_write(void *instance, size_t bytes, char *buf){
	terminal_instance *inst=(terminal_instance*)instance;
	if(inst->mode==bt_vid_text_access_mode::Raw){
		if(inst->pos > maxchar) return 0;
        if(inst->pos+bytes > maxchar) bytes=maxchar-inst->pos;
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

bt_filesize_t terminal_seek(void *instance, bt_filesize_t pos, uint32_t flags){
	terminal_instance *inst=(terminal_instance*)instance;
	size_t ret=0;
    if(inst->mode==bt_vid_text_access_mode::Raw){
        if(flags & FS_Relative) inst->pos+=pos;
		else if(flags & FS_Backwards){
			inst->pos = maxchar - pos;
		}else if(flags == (FS_Relative | FS_Backwards)) inst->pos-=pos;
        else inst->pos=pos;
        ret=inst->pos;
    }else{
        size_t cpos;
        if(flags & FS_Relative){
            cpos=(terminal_row * VGA_WIDTH) + terminal_column;
            cpos+=pos;
		}else if(flags & FS_Backwards){
			cpos = (VGA_HEIGHT * VGA_WIDTH) - pos;
		}else if(flags == (FS_Relative | FS_Backwards)){
			cpos=(terminal_row * VGA_WIDTH) + terminal_column;
            cpos-=pos;
        }else{
            cpos=pos;
        }
        if(cpos > VGA_HEIGHT * VGA_WIDTH){
            dbgpf("KTEXT: Bad seek: %i\n", (int)cpos);
            cpos=VGA_HEIGHT * VGA_WIDTH;
        }
        terminal_row=cpos/VGA_WIDTH;
        terminal_column=cpos-(terminal_row * VGA_WIDTH);
        terminal_poscursor(terminal_row, terminal_column);
        ret=cpos;
        inst->pos=cpos;
    }
	return ret;
}

int terminal_ioctl(void *instance, int fn, size_t bytes, char *buf){
    if(fn == bt_vid_ioctl::GetModeCount) return 1;
    else if(fn==bt_vid_ioctl::GetMode || fn==bt_vid_ioctl::QueryMode){
        memcpy(buf, &mode, max(bytes, sizeof(mode)));
    }else if(fn==bt_vid_ioctl::SetMode){
        if(bytes>=sizeof(mode) && ((bt_vidmode*)buf)->id==mode.id) return 1;
        else return 0;
    }else if(fn==bt_vid_ioctl::SetTextColours){
        if(bytes>=1){
            terminal_color=(uint8_t)*buf;
            return 1;
        }else return 0;
    }else if(fn==bt_vid_ioctl::GetTextColours){
        return terminal_color;
    }else if(fn==bt_vid_ioctl::ClearScreen){
        terminal_move(0, 0);
        for(size_t i=0; i<maxchar; ++i){
            terminal_putchar(' ');
        }
        terminal_move(0, 0);
    }else if(fn==bt_vid_ioctl::GetScrolling){
        return scrolling_enabled;
    }else if(fn==bt_vid_ioctl::SetScrolling){
        scrolling_enabled=*(bool*)buf;
    }else if(fn==bt_vid_ioctl::GetTextAccessMode){
        return ((terminal_instance*)instance)->mode;
    }else if(fn==bt_vid_ioctl::SetTextAccessMode){
        if(bytes==sizeof(bt_vid_text_access_mode::Enum)) {
            ((terminal_instance *) instance)->mode = *(bt_vid_text_access_mode::Enum *) buf;
            return sizeof(bt_vid_text_access_mode::Enum);
        }
    }
	return 0;
}

int terminal_type(void*){
	return driver_types::VID_TEXT;
}

char *terminal_desc(void*){
	return "Kernel built-in VGA text output.";
}

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
	drv_add_device("KTEXT", &terminal_driver, NULL);
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
		if(++terminal_row >= VGA_HEIGHT && scrolling_enabled){
			terminal_scroll();
		}
		terminal_column = 0;
		return;
	}else if(c == '\t'){
		c=' ';
	}
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if ( ++terminal_column >= VGA_WIDTH )
	{
		terminal_column = 0;
		if ( ++terminal_row >= VGA_HEIGHT && scrolling_enabled)
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
	char buf[128]={0};
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

