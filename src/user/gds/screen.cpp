#include "screen.hpp"
#include <cstring>
#include <cstdlib>
#include <sstream>

using namespace std;

Screen::Screen() : BitmapSurface::BitmapSurface(1, 1, true){
	char stdout_path[BT_MAX_PATH]={0};
	bt_getenv("STDOUT", stdout_path, BT_MAX_PATH);

	fh=bt_fopen(stdout_path, FS_Read | FS_Write);
	bt_terminal_mode::Enum terminal_mode=bt_terminal_mode::Video;
	bt_fioctl(fh, bt_terminal_ioctl::SetMode, sizeof(terminal_mode), (char*)&terminal_mode);

	buffer=NULL;
	buffersize=0;
	original_mode.bpp=0;
}

Screen::~Screen(){
	RestoreMode();
	bt_fclose(fh);
	if(buffer) delete buffer;
}

void Screen::RestoreMode(){
	if(original_mode.bpp){
		bt_fioctl(fh, bt_vid_ioctl::SetMode, sizeof(original_mode), (char*)&original_mode);
	}
}

void Screen::BufferPutPixel(uint32_t x, uint32_t y, uint32_t value) {
	if(x > current_mode.width || y > current_mode.height) return;
	if(!buffer) return;
	size_t pixelpos=(y * current_mode.width) + x;
	if(current_mode.bpp == 8){
		if(pixelpos >= buffersize) return;
		buffer[pixelpos]=(uint8_t)value;
	}else if(current_mode.bpp==4){
		uint8_t c=(uint8_t)value;
		size_t bufpos=pixelpos/2;
		if(bufpos >= buffersize) return;
		if(pixelpos % 2){
			buffer[bufpos] = (uint8_t)((buffer[bufpos] & 0xF0) | (0x0F & c));
		}else{
			buffer[bufpos] = (uint8_t)((buffer[bufpos] & 0x0F) | (0xF0 & (c << 4)));
		}
	}
}

uint32_t Screen::BufferGetPixel(uint32_t x, uint32_t y){
	if(x > current_mode.width || y > current_mode.height) return 0;
	if(!buffer) return 0;
	size_t pixelpos=(y * current_mode.width) + x;
	if(current_mode.bpp == 8){
		return buffer[pixelpos];
	}else if(current_mode.bpp==4){
		uint8_t c=0;
		size_t bufpos=pixelpos/2;
		if(pixelpos % 2){
			c = (uint8_t)(buffer[bufpos] & 0x0F);
		}else{
			c = (uint8_t)((buffer[bufpos] >> 4) & 0x0F);
		}
		return c;
	}
	return 0;
}

size_t Screen::GetBytePos(uint32_t x, uint32_t y) {
	size_t ret=(y * current_mode.width) + x;
	if(current_mode.bpp >= 8) ret *= (current_mode.bpp / 8);
	else ret /= (8 / current_mode.bpp);
	return ret;
}

size_t Screen::BytesPerPixel() {
	if(current_mode.bpp <=8) return 1;
	else return current_mode.bpp / 8;
}

bool Screen::SetMode(uint32_t w, uint32_t h, uint8_t bpp) {
	bt_fioctl(fh, bt_vid_ioctl::QueryMode, sizeof(original_mode), (char*)&original_mode);
	size_t modecount=bt_fioctl(fh, bt_vid_ioctl::GetModeCount, 0, NULL);
	bt_vidmode bestmode;
	bestmode.bpp=0;
	bt_vidmode mode;
	for(size_t i=0; i<modecount; ++i) {
		mode.id = i;
		bt_fioctl(fh, bt_vid_ioctl::GetMode, sizeof(mode), (char *) &mode);
		if(mode.textmode) continue;
		if(mode.width >= w && mode.height >= h && mode.bpp >=bpp){
			if(bestmode.bpp && mode.width <= bestmode.width && mode.height <= bestmode.height && mode.bpp <= bestmode.bpp){
				bestmode = mode;
			}else if(!bestmode.bpp){
				bestmode = mode;
			}
		}
	}
	if(bestmode.bpp){
		bt_fioctl(fh, bt_vid_ioctl::SetMode, sizeof(bestmode), (char *) &bestmode);
		current_mode=bestmode;
		if(current_mode.bpp >= 16){
			BitmapSurface::Resize(current_mode.width, current_mode.height, false);
		}else{
			BitmapSurface::Resize(current_mode.width, current_mode.height, true);
			for(size_t p=0; p<256; ++p){
				size_t idx=(p % (1 << current_mode.bpp));
				bt_video_palette_entry entry;
				entry.index=idx;
				bt_fioctl(fh, bt_vid_ioctl::GetPaletteEntry, sizeof(entry), (char*)&entry);
				image->ColorAllocate(entry.r, entry.g, entry.b);
			}
		}
		if(buffer) delete buffer;
		if(current_mode.bpp >=8) buffersize = current_mode.width * current_mode.height * (current_mode.bpp / 8);
		else buffersize = current_mode.width * current_mode.height / (8 / current_mode.bpp);
		buffer=new uint8_t[buffersize]();
		bt_fseek(fh, 0, false);
		bt_fread(fh, buffersize, (char*)buffer);
		bool autohide = false;
		bt_fioctl(fh, bt_terminal_ioctl::PointerAutoHide, sizeof(autohide), (char*)&autohide);
		return true;
	}
	return false;
}

void Screen::UpdateScreen(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
	bool hide_cursor = false;	
	if (!x && !y && !w && !h) {
		w = current_mode.width - 1;
		h = current_mode.height - 1;
	}
	if(cursor_on){
		hide_cursor = true;
		bt_terminal_pointer_info pointer_info;
		bt_fioctl(fh, bt_terminal_ioctl::GetPointerInfo, sizeof(pointer_info), (char*)&pointer_info);
		int32_t sxpos = pointer_info.x;
		int32_t sypos = pointer_info.y;
		sxpos -= cursor_bmp_info.spot_x;
		sypos -= cursor_bmp_info.spot_y;
		uint32_t x1 = max(0, sxpos);
		uint32_t y1 = max(0, sypos);
		uint32_t x2 = x1 + cursor_bmp_info.w;
		uint32_t y2 = y1 + cursor_bmp_info.h;
		if(x1 < x && x2 < x) hide_cursor = false; 
		if(x1 > x + w && x2 > x + w)  hide_cursor = false;
		if(y1 < y && y2 < y) hide_cursor = false; 
		if(y1 > y + h && y2 > y + h) hide_cursor = false; 
	}
	if(y > current_mode.height) return;
	if(x > current_mode.width) return;
	if(x + w >= current_mode.width) w = current_mode.width - x - 1;
	if(y + h >= current_mode.height) h = current_mode.height - y - 1;
	for(uint32_t row=y; row <= y+h; ++row){
		if(row > current_mode.height) break;
		for(uint32_t col=x; col <= x+w; ++col){
			if(col > current_mode.width) break;
			uint32_t value;
			if(image->IsTrueColor()) {
				value=image->GetTrueColorPixel(col, row);
			}else{
				value=image->GetPixel(col, row);
			}
			BufferPutPixel(col, row, value);
		}
	}
	bt_fioctl(fh, bt_terminal_ioctl::PointerFreeze, 0, NULL);
	if(hide_cursor) bt_fioctl(fh, bt_terminal_ioctl::HidePointer, 0, NULL);
	if(w == current_mode.width && h == current_mode.height) {
		bt_fseek(fh, 0, false);
		bt_fwrite(fh, buffersize, (char *) buffer);
	}else{
		for(size_t row=y; row <= y+h; ++row){
			size_t start= GetBytePos(x, row);
			if(start > buffersize) break;
			size_t end= GetBytePos(x+w, row) + BytesPerPixel() + 2;
			if(end > buffersize) end=buffersize;
			size_t bytes = end - start;
			bt_fseek(fh, start, false);
			bt_fwrite(fh, bytes, (char*)&buffer[start]);
		}
	}
	if(hide_cursor) bt_fioctl(fh, bt_terminal_ioctl::ShowPointer, 0, NULL);
	bt_fioctl(fh, bt_terminal_ioctl::PointerUnfreeze, 0, NULL);
}

void Screen::ShowCursor() {
	bt_fioctl(fh, bt_terminal_ioctl::ShowPointer, 0, NULL);
	cursor_on=true;
}

void Screen::HideCursor() {
	bt_fioctl(fh, bt_terminal_ioctl::HidePointer, 0, NULL);
	cursor_on=false;
}

void Screen::SetCursorImage(const GD::Image &img, uint32_t hotx, uint32_t hoty) {
	bt_terminal_pointer_bitmap bmp;
	bmp.spot_x=hotx;
	bmp.spot_y=hoty;
	bmp.bpp=current_mode.bpp;
	bmp.w=img.Width();
	bmp.h=img.Height();
	cursor_bmp_info = bmp;
	cursor_bmp_info.datasize = 0;
	uint32_t transparent=img.GetTransparent();
	bmp.transparent=transparent;//image->ColorClosest(img.Red(transparent), img.Green(transparent), img.Blue(transparent));
	size_t datasize;
	if(current_mode.bpp >=8) datasize = bmp.w * bmp.h * (bmp.bpp / 8);
	else datasize = bmp.w * bmp.h / (8 / bmp.bpp);
	uint8_t *data=new uint8_t[datasize]();
	for(uint32_t x=0; x<bmp.w; ++x){
		for(uint32_t y=0; y<bmp.h; ++y){
			uint32_t value=img.GetPixel(x, y);
			if(value != transparent) value=image->ColorClosest(img.Red(value), img.Green(value), img.Blue(value));
			size_t pixelpos=(y * bmp.w) + x;
			if(bmp.bpp == 8){
				if(pixelpos >= datasize) continue;
				data[pixelpos]=(uint8_t)value;
			}else if(bmp.bpp==4){
				uint8_t c=(uint8_t)value;
				size_t bufpos=pixelpos/2;
				if(bufpos >= datasize) continue;
				if(pixelpos % 2){
					data[bufpos] = (uint8_t)((data[bufpos] & 0xF0) | (0x0F & c));
				}else{
					data[bufpos] = (uint8_t)((data[bufpos] & 0x0F) | (0xF0 & (c << 4)));
				}
			}
		}
	}
	bmp.datasize=datasize;
	void *complete=malloc(sizeof(bmp) + datasize);
	memcpy(complete, &bmp, sizeof(bmp));
	memcpy((char*)complete+sizeof(bmp), data, datasize);
	bt_fioctl(fh, bt_terminal_ioctl::SetPointerBitmap, sizeof(bmp)+datasize, (char*)complete);
	free(complete);
	delete data;
}

gds_SurfaceType::Enum Screen::GetType(){
	return gds_SurfaceType::Screen;
}

shared_ptr<Screen> GetScreen(){
	static shared_ptr<Screen> screen;
	if(!screen) screen.reset(new Screen());
	return screen;
}
