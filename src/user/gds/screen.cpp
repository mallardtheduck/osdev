#include "screen.hpp"
#include <cstring>
#include <cstdlib>

Screen::Screen(){
	char stdout_path[BT_MAX_PATH]={0};
	bt_getenv("STDOUT", stdout_path, BT_MAX_PATH);

	fh=bt_fopen(stdout_path, FS_Read | FS_Write);
	bt_terminal_mode::Enum terminal_mode=bt_terminal_mode::Video;
	bt_fioctl(fh, bt_terminal_ioctl::SetMode, sizeof(terminal_mode), (char*)&terminal_mode);

	image=NULL;
	buffer=NULL;
	buffersize=0;
	original_mode.bpp=0;
}

Screen::~Screen(){
	if(original_mode.bpp){
		bt_fioctl(fh, bt_vid_ioctl::SetMode, sizeof(original_mode), (char*)&original_mode);
	}
	bt_fclose(fh);
	if(image) delete image;
	if(buffer) delete buffer;
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
		if(image) delete image;
		if(current_mode.bpp >= 16){
			image= new GD::Image(current_mode.width, current_mode.height, true);
		}else{
			image= new GD::Image(current_mode.width, current_mode.height, false);
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
		return true;
	}
	return false;
}

void Screen::UpdateScreen(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
	if (!x && !y && !w && !h) {
		w = current_mode.width;
		h = current_mode.height;
	}
	if(y > current_mode.height) return;
	if(x > current_mode.width) return;
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
	if(cursor_on) bt_fioctl(fh, bt_terminal_ioctl::HidePointer, 0, NULL);
	if(w == current_mode.width && h == current_mode.height) {
		bt_fseek(fh, 0, false);
		bt_fwrite(fh, buffersize, (char *) buffer);
	}else{
		for(size_t row=y; row <= y+h; ++row){
			size_t start= GetBytePos(x, row);
			if(start > buffersize) break;
			size_t end= GetBytePos(x+w, row) + BytesPerPixel() + 1;
			if(end > buffersize) end=buffersize;
			size_t bytes = end - start;
			bt_fseek(fh, start, false);
			bt_fwrite(fh, bytes, (char*)&buffer[start]);
		}
	}
	if(cursor_on) bt_fioctl(fh, bt_terminal_ioctl::ShowPointer, 0, NULL);
}

GD::Image *Screen::GetImage() {
	return image;
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
	int transparent=img.GetTransparent();
	bmp.transparent=image->ColorClosest(img.Red(transparent), img.Green(transparent), img.Blue(transparent));
	size_t datasize;
	if(current_mode.bpp >=8) datasize = bmp.w * bmp.h * (bmp.bpp / 8);
	else datasize = bmp.w * bmp.h / (8 / bmp.bpp);
	uint8_t *data=new uint8_t[datasize]();
	for(uint32_t x=0; x<bmp.w; ++x){
		for(uint32_t y=0; y<bmp.h; ++y){
			uint32_t value=img.GetPixel(x, y);
			value=image->ColorClosest(img.Red(value), img.Green(value), img.Blue(value));
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