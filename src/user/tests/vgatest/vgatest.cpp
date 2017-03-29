#include <btos.h>
#include <stdio.h>
#include <dev/video_dev.h>
#include <dev/terminal.h>
#include <crt_support.h>
#include <cstdlib>
#include <iostream>

#include "../../../other/art/BTOS-bootscreen-mono.xbm"
#include "pointers.hpp"

using namespace std;

bt_filehandle open_device(){
    bt_filehandle stdout_fh=btos_get_handle(fileno(stdout));
    int devtype= bt_fioctl(stdout_fh, bt_ioctl::DevType, 0, NULL);
    if(devtype!=driver_types::TERMINAL){
        printf("Output device is not a terminal.\n");
        return 0;
    }
    char stdout_path[BT_MAX_PATH]={0};
    bt_getenv("STDOUT", stdout_path, BT_MAX_PATH);
    bt_filehandle dev_fh=bt_fopen(stdout_path, FS_Read | FS_Write);
    bt_terminal_mode::Enum terminal_mode=bt_terminal_mode::Video;
    bt_fioctl(dev_fh, bt_terminal_ioctl::SetTerminalMode, sizeof(terminal_mode), (char*)&terminal_mode);
    return dev_fh;
}

void load_btos_bootscreen(uint8_t *buffer){
    for(size_t pixpos=0; pixpos<(640*480); ++pixpos){
        size_t byte=pixpos >> 3;
        size_t bit=pixpos & 7;
        size_t bufpos=pixpos/2;
        uint8_t imask=1 << bit;
        bool value=!(BTOS_bootscreen_mono_bits[byte] & imask);
        if(pixpos % 2){
            if(value) {
                buffer[bufpos] |= 0x0F;
            }else{
                buffer[bufpos] &= 0xF0;
            }
        }else{
            if(value) {
                buffer[bufpos] |= 0xF0;
            }else{
                buffer[bufpos] &= 0x0F;
            }
        }
    }
}

typedef union{
	uint32_t v32;
	char v8[4];
} pxl32;

void testmode(bt_handle_t fh, const bt_vidmode &mode, const bt_vidmode &original_mode){
	if (!mode.textmode) {
		bt_fioctl(fh, bt_vid_ioctl::SetMode, sizeof(mode), (char *) &mode);
		bt_fseek(fh, 0, false);
		size_t buffersize = (mode.height * mode.bytesPerLine);
		uint8_t *buffer=(uint8_t*)malloc(buffersize);
		if(!buffer){
			bt_fioctl(fh, bt_vid_ioctl::SetMode, sizeof(original_mode), (char*)&original_mode);
			printf("Could not allocate buffer for memory-mapping!\n");
			return;
		}
		bt_handle m= bt_mmap(fh, 0, (char*)buffer, buffersize);
		pxl32 pixel;
		pixel.v32 = 0;
		for (size_t i = 0; i < buffersize; ++i) {
			/*uint32_t y=i/mode.width;
			if(mode.bpp==4) y/=2;
			uint8_t col = y % (1 << mode.bpp);
			if(mode.bpp==4) col |= col << 4;
			buffer[i]=col;*/
			char q = pixel.v8[i % 4];
			buffer[i] = q;
			pixel.v32++;
		}
		bt_fflush(fh);
		if(mode.bpp == 32){
			bt_terminal_pointer_bitmap *pointer_bmp = get_pointer_bmp_32bpp();
			bt_fioctl(fh, bt_terminal_ioctl::SetPointerBitmap, sizeof(bt_terminal_pointer_bitmap)+pointer_bmp->datasize, (char*)pointer_bmp);
			bt_fioctl(fh, bt_terminal_ioctl::ShowPointer, 0, NULL);
			getchar();
			bt_fioctl(fh, bt_terminal_ioctl::HidePointer, 0, NULL);
			free(pointer_bmp);
		}else if(mode.bpp == 24){
			bt_terminal_pointer_bitmap *pointer_bmp = get_pointer_bmp_24bpp();
			bt_fioctl(fh, bt_terminal_ioctl::SetPointerBitmap, sizeof(bt_terminal_pointer_bitmap)+pointer_bmp->datasize, (char*)pointer_bmp);
			bt_fioctl(fh, bt_terminal_ioctl::ShowPointer, 0, NULL);
			getchar();
			bt_fioctl(fh, bt_terminal_ioctl::HidePointer, 0, NULL);
			free(pointer_bmp);
		}else if(mode.bpp == 16){
			bt_terminal_pointer_bitmap *pointer_bmp = get_pointer_bmp_16bpp();
			bt_fioctl(fh, bt_terminal_ioctl::SetPointerBitmap, sizeof(bt_terminal_pointer_bitmap)+pointer_bmp->datasize, (char*)pointer_bmp);
			bt_fioctl(fh, bt_terminal_ioctl::ShowPointer, 0, NULL);
			getchar();
			bt_fioctl(fh, bt_terminal_ioctl::HidePointer, 0, NULL);
			free(pointer_bmp);
		}else if(mode.bpp == 8){
			bt_fioctl(fh, bt_terminal_ioctl::SetPointerBitmap, sizeof(pointer_bmp_8bpp)+pointer_bmp_8bpp.datasize, (char*)&pointer_bmp_8bpp);
			bt_fioctl(fh, bt_terminal_ioctl::ShowPointer, 0, NULL);
			getchar();
			bt_fioctl(fh, bt_terminal_ioctl::HidePointer, 0, NULL);
		}else if(mode.bpp == 4){
			bt_fioctl(fh, bt_terminal_ioctl::SetPointerBitmap, sizeof(pointer_bmp_4bpp)+pointer_bmp_4bpp.datasize, (char*)&pointer_bmp_4bpp);
			bt_fioctl(fh, bt_terminal_ioctl::ShowPointer, 0, NULL);
			getchar();
			bt_fioctl(fh, bt_terminal_ioctl::HidePointer, 0, NULL);
		}
		if(mode.width==640 && mode.height==480 && mode.bpp==4){
			load_btos_bootscreen(buffer);
			bt_fflush(fh);
			getchar();
		}
		bt_closehandle(m);
		free(buffer);
	}
}

int main(){
    bt_filehandle fh=open_device();
    if(!fh) return -1;
    bt_vidmode original_mode;
    bt_fioctl(fh, bt_vid_ioctl::QueryMode, sizeof(original_mode), (char*)&original_mode);
    size_t modecount=bt_fioctl(fh, bt_vid_ioctl::GetModeCount, 0, NULL);
    bt_vidmode mode;
    /*for(size_t i=0; i<modecount; ++i) {
        mode.id = i;
        bt_fioctl(fh, bt_vid_ioctl_GetMode, sizeof(mode), (char *) &mode);
        if (!mode.textmode) {
            bt_fioctl(fh, bt_vid_ioctl_SetMode, sizeof(mode), (char *) &mode);
            bt_fseek(fh, 0, false);
            size_t buffersize = (mode.width * mode.height);
            if (mode.bpp == 4) buffersize /= 2;
            else buffersize *= (mode.bpp / 8);
            for (size_t i = 0; i < buffersize; ++i) {
                //uint32_t y=i/mode.width;
                //if(mode.bpp==4) y/=2;
                //uint8_t col = y % (1 << mode.bpp);
                //if(mode.bpp==4) col |= col << 4;
                //bt_fwrite(fh, 1, (char *) &col);
                char q = (char)i;
                bt_fwrite(fh, 1, &q);
            }
            getchar();
        }
    }*/
    for(size_t i=0; i<modecount; ++i) {
		mode.id = i;
		bt_fioctl(fh, bt_vid_ioctl::GetMode, sizeof(mode), (char *) &mode);
		if(mode.textmode) continue;
		cout << "Next mode: " << mode.width << " x " << mode.height << " " << mode.bpp << "bpp" << endl;
		cout << "Test?" << endl;
		char c = getchar();
		char q = '\0';
		while(q != '\n') q = getchar();
		if(c == 'y') {
			testmode(fh, mode, original_mode);
			bt_fioctl(fh, bt_vid_ioctl::SetMode, sizeof(original_mode), (char*)&original_mode);
		}
    }
    bt_fioctl(fh, bt_vid_ioctl::SetMode, sizeof(original_mode), (char*)&original_mode);
    for(size_t i=0; i<256; ++i){
        bt_video_palette_entry entry;
        entry.index=i;
        bt_fioctl(fh, bt_vid_ioctl::GetPaletteEntry, sizeof(entry), (char*)&entry);
        printf("Palette entry %i: (%i, %i, %i)\n", (int)entry.index, entry.r, entry.g, entry.b);
        if(!((i + 1) % (original_mode.height - 1))) getchar();
    }
    return 0;
}
