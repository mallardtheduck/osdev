#include "ops.hpp"
#include "device.hpp"
#include "modes.hpp"
#include "video_dev.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

static size_t text_row;
static size_t text_column;
static uint8_t text_color;
static bool scrolling_enabled=true;

void text_writestring(const char* data);
void text_poscursor(size_t row, size_t col);
void text_move(int x, int y);
void text_putchar(char c);
void text_putentryat(char c, uint8_t color, size_t x, size_t y);

size_t text_read(vga_instance *inst, size_t bytes, char *buf){
    size_t maxchar=current_mode->vidmode.width * current_mode->vidmode.height * 2;
    if(inst->mode==bt_vid_text_access_mode::Raw){
        if(inst->pos > maxchar) return 0;
        if(inst->pos+bytes > maxchar) bytes=maxchar-inst->pos;
        memcpy(buf, (char*)text_memory+inst->pos, bytes);
        inst->pos+=bytes;
    }else{
        size_t chars=maxchar/2;
        if(inst->pos > chars) return 0;
        if(inst->pos+bytes > chars) bytes=chars-inst->pos;
        for(size_t i=0; i<bytes; ++i){
            buf[i]=((uint16_t*)text_memory)[inst->pos+i] & 0xFF;
        }
        inst->pos+=bytes;
    }
    return bytes;
}

size_t text_write(vga_instance *inst, size_t bytes, char *buf){
    size_t maxchar=current_mode->vidmode.width * current_mode->vidmode.height * 2;
    if(inst->mode==bt_vid_text_access_mode::Raw){
        if(inst->pos > maxchar) return 0;
        if(inst->pos+bytes > maxchar) bytes=maxchar-inst->pos;
        memcpy((char*)text_memory+inst->pos, buf, bytes);
        inst->pos+=bytes;
        return bytes;
    }else{
        char *obuf=(char*)malloc(bytes+1);
        memset(obuf, 0, bytes+1);
        memcpy(obuf, buf, bytes);
        text_writestring(obuf);
        free(obuf);
        return bytes;
    }
}

size_t text_seek(vga_instance *inst, size_t pos, uint32_t flags){
    size_t ret=0;
    if(inst->mode==bt_vid_text_access_mode::Raw){
        if(flags & FS_Relative) inst->pos+=pos;
		else if(flags & FS_Backwards){
			inst->pos = (current_mode->vidmode.height * current_mode->vidmode.width * 2) - pos;
		}else if(flags == (FS_Relative | FS_Backwards)) inst->pos-=pos;
        else inst->pos=pos;
        ret=inst->pos;
    }else{
        size_t cpos;
        if(flags & FS_Relative){
            cpos=(text_row * current_mode->vidmode.width) + text_column;
            cpos+=pos;
		}else if(flags & FS_Backwards){
			cpos = (current_mode->vidmode.height * current_mode->vidmode.width) - pos;
		}else if(flags == (FS_Relative | FS_Backwards)){
			cpos=(text_row * current_mode->vidmode.width) + text_column;
            cpos-=pos;
        }else{
            cpos=pos;
        }
        if(cpos > current_mode->vidmode.height * current_mode->vidmode.width){
            dbgpf("VGA: Bad text seek: %i\n", cpos);
            cpos=current_mode->vidmode.height * current_mode->vidmode.width;
        }
        text_row=cpos/current_mode->vidmode.width;
        text_column=cpos-(text_row * current_mode->vidmode.width);
        text_poscursor(text_row, text_column);
        ret=cpos;
        inst->pos=cpos;
    }
    return ret;
}

int text_ioctl(vga_instance *inst, int fn, size_t bytes, char *buf){
    size_t maxchar=current_mode->vidmode.width * current_mode->vidmode.height * 2;
    if(fn==bt_vid_ioctl::SetTextColours){
        if(bytes>=1){
            text_color=(uint8_t)*buf;
            return 1;
        }else return 0;
    }else if(fn==bt_vid_ioctl::GetTextColours){
        return text_color;
    }else if(fn==bt_vid_ioctl::ClearScreen){
        text_move(0, 0);
        for(size_t i=0; i<maxchar; ++i){
            text_putchar(' ');
        }
        text_move(0, 0);
    }else if(fn==bt_vid_ioctl::GetScrolling){
        return scrolling_enabled;
    }else if(fn==bt_vid_ioctl::SetScrolling){
        scrolling_enabled=*(bool*)buf;
    }else if(fn==bt_vid_ioctl::GetTextAccessMode){
        return inst->mode;
    }else if(fn==bt_vid_ioctl::SetTextAccessMode){
        if(bytes==sizeof(bt_vid_text_access_mode::Enum)) {
            inst->mode = *(bt_vid_text_access_mode::Enum *) buf;
            return sizeof(bt_vid_text_access_mode::Enum);
        }
    }
    return 0;
}

uint8_t make_color(uint8_t fg, uint8_t bg)
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

void text_scroll(){
    for(size_t y=0; y<current_mode->vidmode.height; ++y){
        for(size_t x=0; x<current_mode->vidmode.width; ++x){
            const size_t source = y * current_mode->vidmode.width + x;
            if(y){
                const size_t dest = (y-1) * current_mode->vidmode.width + x;
                ((uint16_t*)text_memory)[dest]=((uint16_t*)text_memory)[source];
            }
            text_putentryat(' ', text_color, x, y);
        }
    }
    text_column=0;
    text_row=current_mode->vidmode.height-1;
    text_poscursor(text_row, text_column);
}

void text_setcolor(uint8_t color)
{
    text_color = color;
}

void text_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    size_t index = y * current_mode->vidmode.width + x;
    ((uint16_t*)text_memory)[index] = make_vgaentry(c, color);
}

void text_putchar(char c)
{
    if(c == '\n'){
        if(++text_row >= current_mode->vidmode.height && scrolling_enabled){
            text_scroll();
        }
        text_column = 0;
        return;
    }else if(c == '\t'){
        c=' ';
    }
    text_putentryat(c, text_color, text_column, text_row);
    if ( ++text_column >= current_mode->vidmode.width )
    {
        text_column = 0;
        if ( ++text_row >= current_mode->vidmode.height && scrolling_enabled)
        {
            text_scroll();
        }
    }
}

void text_poscursor(size_t row, size_t col){
    uint16_t position=(row*80) + col;

    write_crtc(CRTC_Registers::CursorLocLow, (unsigned char)(position&0xFF));
    write_crtc(CRTC_Registers::CursorLocHigh, (unsigned char )((position>>8)&0xFF));
}

void text_writestring(const char* data)
{
    size_t datalen = strlen(data);
    for (size_t i = 0; i < datalen; i++) text_putchar(data[i]);
    text_poscursor(text_row, text_column);
}

void text_move(int x, int y){
    text_row=y;
    text_column=x;
    text_poscursor(text_row, text_column);
}

void init_text(){
    text_row = 0;
    text_column = 0;
    text_color = make_color(7, 0);
    for ( size_t y = 0; y < current_mode->vidmode.height; y++ )
    {
        for ( size_t x = 0; x < current_mode->vidmode.width; x++ )
        {
            const size_t index = y * current_mode->vidmode.width + x;
            ((uint16_t*)text_memory)[index] = make_vgaentry(' ', text_color);
        }
    }
}