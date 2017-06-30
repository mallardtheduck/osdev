#include "screen.hpp"
#include <cstring>
#include <cstdlib>
#include <dev/rtc.h>
#include <dev/terminal_ioctl.h>

using namespace std;

static const size_t thread_stack_size = (4 * 1024);

static size_t max_syscall_items = 256;
static bt_syscall_item syscall_items[256];

void screen_update_thread(void *){
	Screen *pthis = GetScreen().get();
	bool quit = false;
	deque<Screen::update> batch;
	while(true){
		bt_wait_atom(pthis->sync_atom, bt_atom_compare::GreaterThan, 0);
		bt_lock(pthis->update_q_lock);
		batch.swap(pthis->update_q);
		bt_modify_atom(pthis->sync_atom, bt_atom_modify::Set, 0);
		bt_unlock(pthis->update_q_lock);
		//DBG("GDS: Update batch size: " << batch.size());
		bt_term_PointerFreeze();
		bool hide_pointer = false;
		size_t callcount = 0;
		for(const auto &up : batch){
			if(up.data == NULL){
				quit = true;
				break;
			}
			if(up.hide_pointer) hide_pointer = true;
			syscall_items[callcount++] = {BT_FSEEK, pthis->fh, (uint32_t)&up.pos, FS_Set};
			syscall_items[callcount++] = {BT_FWRITE, pthis->fh, up.size, (uint32_t)up.data};
			if(callcount == max_syscall_items){
				if(hide_pointer) bt_term_HidePointer();
				bt_multi_call(syscall_items, callcount);
				if(hide_pointer) bt_term_ShowPointer();
				callcount = 0;
			}
		}
		if(quit) return;
		if(callcount){
			if(hide_pointer) bt_term_HidePointer();
			bt_multi_call(syscall_items, callcount);
			if(hide_pointer) bt_term_ShowPointer();
		}
		bt_lock(pthis->update_q_lock);
		batch.clear();
		bt_unlock(pthis->update_q_lock);
		bt_term_PointerUnfreeze();
		bt_rtc_sleep(15);
	}
}

Screen::Screen() : BitmapSurface::BitmapSurface(1, 1, true){
	char stdout_path[BT_MAX_PATH]={0};
	bt_getenv("STDOUT", stdout_path, BT_MAX_PATH);

	fh=bt_fopen(stdout_path, FS_Read | FS_Write);
	bt_term_SetTerminalMode(bt_terminal_mode::Video);
	bt_term_stdout();

	buffer=NULL;
	buffersize=0;
	original_mode.bpp=0;
	
	sync_atom = bt_create_atom(0);
	update_q_lock = bt_create_lock();
}

Screen::~Screen(){
	QueueUpdate(0, 0, 0, false);
	bt_wait_thread(update_thread);
	RestoreMode();
	bt_fclose(fh);
	if(buffer) delete buffer;
}

void Screen::RestoreMode(){
	if(original_mode.bpp){
		if(update_thread){
			QueueUpdate(0, 0, 0, false);
			bt_wait_thread(update_thread);
		}
		bt_term_SetScreenMode(original_mode);
	}
}

bool Screen::BufferPutPixel(uint32_t x, uint32_t y, uint32_t value) {
	if(x > current_mode.width || y > current_mode.height) return false;
	if(!buffer) return false;
	//if(BufferGetPixel(x, y) == value) return false;
	size_t pixelpos=(y * current_mode.width) + x;
	if(current_mode.bpp > 8){
		if(pixel_conversion_required) value = ConvertPixel(value);
		size_t depth = (current_mode.bpp / 8);
		size_t bufferpos = pixelpos * depth;
		memcpy(&buffer[bufferpos], &value, depth);
	}else if(current_mode.bpp == 8){
		if(pixelpos >= buffersize) return false;
		buffer[pixelpos]=(uint8_t)value;
	}else if(current_mode.bpp==4){
		uint8_t c=(uint8_t)value;
		size_t bufpos=pixelpos/2;
		if(bufpos >= buffersize) return false;
		if(pixelpos % 2){
			buffer[bufpos] = (uint8_t)((buffer[bufpos] & 0xF0) | (0x0F & c));
		}else{
			buffer[bufpos] = (uint8_t)((buffer[bufpos] & 0x0F) | (0xF0 & (c << 4)));
		}
	}
	return true;
}

uint32_t Screen::BufferGetPixel(uint32_t x, uint32_t y){
	if(x > current_mode.width || y > current_mode.height) return 0;
	if(!buffer) return 0;
	size_t pixelpos=(y * current_mode.width) + x;
	if(current_mode.bpp > 8){
		size_t depth = (current_mode.bpp / 8);
		size_t bufferpos = pixelpos * depth;
		uint32_t value = 0;
		memcpy(&value, &buffer[bufferpos], depth);
		return value;
	}else if(current_mode.bpp == 8){
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

size_t Screen::GetBytePos(uint32_t x, uint32_t y, bool upper) {
	if(current_mode.bpp >= 8){
		size_t depth = (current_mode.bpp / 8);
		size_t ret=(y * current_mode.bytesPerLine) + (x * depth);
		return ret;
	} else {
		size_t ret=(y * current_mode.width) + x;
		ret /= (8 / current_mode.bpp);
		ret += upper ? 1 : 0;
		return ret;
	}
}

size_t Screen::BytesPerPixel() {
	if(current_mode.bpp <=8) return 1;
	else return current_mode.bpp / 8;
}

static inline uint32_t scale_value(uint8_t value, uint8_t bits){
	if(bits < 8){
		uint8_t diff = 8 - bits;
		value >>= diff;
	}
	return value;
}

uint32_t Screen::ConvertPixel(uint32_t pix){
	if(!pixel_conversion_required) return pix;
	if(image->IsTrueColor()){
		uint8_t red = gdTrueColorGetRed(pix);
		uint8_t green = gdTrueColorGetGreen(pix);
		uint8_t blue = gdTrueColorGetBlue(pix);
		uint32_t redPart = scale_value(red, current_mode.rBits) << current_mode.rPos;
		uint32_t greenPart = scale_value(green, current_mode.gBits) << current_mode.gPos;
		uint32_t bluePart = scale_value(blue, current_mode.bBits) << current_mode.bPos;
		return (redPart | greenPart | bluePart);
	}else{
		return pix;
	}
}

void Screen::QueueUpdate(size_t pos, size_t size, char *data, bool hide_pointer){
	update up = {pos, size, data, hide_pointer};
	bt_lock(update_q_lock);
	update_q.push_back(up);
	bt_modify_atom(sync_atom, bt_atom_modify::Add, 1);
	bt_unlock(update_q_lock);
}

bool Screen::SetMode(uint32_t w, uint32_t h, uint8_t bpp) {
	DBG("GDS: Setting mode " << w << "x" << h << " " << (int)bpp << "bpp.");
	original_mode = bt_term_QueryScreenMode();
	size_t modecount=bt_term_GetScreenModeCount();
	bt_vidmode bestmode;
	bestmode.bpp=0;
	bt_vidmode mode;
	for(size_t i=0; i<modecount; ++i) {
		mode = bt_term_GetScreenMode(i);
		if(mode.textmode) continue;
		if(mode.width >= w && mode.height >= h && mode.bpp >= bpp){
			if(bestmode.bpp && mode.width <= bestmode.width && mode.height <= bestmode.height && mode.bpp <= bestmode.bpp){
				bestmode = mode;
			}else if(!bestmode.bpp){
				bestmode = mode;
			}
		}
	}
	DBG("GDS: Found mode " << bestmode.width << "x" << bestmode.height << " " << (int)bestmode.bpp << "bpp.");
	if(bestmode.bpp){
		if(update_thread){
			QueueUpdate(0, 0, 0, false);
			bt_wait_thread(update_thread);
		}
		
		bt_term_SetScreenMode(bestmode);
		current_mode=bestmode;
		if(current_mode.bpp >= 16){
			BitmapSurface::Resize(current_mode.width, current_mode.height, false);
		}else{
			BitmapSurface::Resize(current_mode.width, current_mode.height, true);
			for(size_t p=0; p<256; ++p){
				size_t idx=(p % (1 << current_mode.bpp));
				bt_video_palette_entry entry = bt_term_GetPaletteEntry(idx);
				image->ColorAllocate(entry.r, entry.g, entry.b);
			}
		}
		if(buffer) delete buffer;
		if(current_mode.bpp >=8) buffersize = current_mode.width * current_mode.height * (current_mode.bpp / 8);
		else buffersize = current_mode.width * current_mode.height / (8 / current_mode.bpp);
		buffer=new uint8_t[buffersize]();
		bt_fseek(fh, 0, false);
		bt_fread(fh, buffersize, (char*)buffer);
		bt_term_PointerAutoHide(false);
		pixel_conversion_required = true;
		DBG("GDS: bpp: " << bestmode.bpp);
		if(bestmode.bpp == 24 || bestmode.bpp == 32){
			DBG("GDS: rBits: " << (int)bestmode.rBits << " gBits: " << (int)bestmode.gBits << " bBits: " << (int)bestmode.bBits);
			if(bestmode.rBits == 8 && bestmode.gBits == 8 && bestmode.bBits == 8){
				DBG("GDS: rPos: " << (int)bestmode.rPos << " gPos: " << (int)bestmode.gPos << " bPos: " << (int)bestmode.bPos);
				if(bestmode.rPos == 16 && bestmode.gPos == 8 && bestmode.bPos == 0) {
					bt_zero("GDS: No pixel conversion required for this mode.\n");
					pixel_conversion_required = false;
				}
			}
		}
		update_thread = btos_create_thread(&screen_update_thread, (void*)this, thread_stack_size);
		return true;
	}
	return false;
}

void Screen::UpdateScreen(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
	//uint64_t update_start = bt_rtc_millis();
	bool hide_cursor = false;	
	if (!x && !y && !w && !h) {
		w = current_mode.width;
		h = current_mode.height;
	}
	if(!w || !h) return;
	if(cursor_on){
		hide_cursor = true;
		bt_terminal_pointer_info pointer_info = bt_term_GetPointerInfo();
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
	if(x + w > current_mode.width) w = current_mode.width - x;
	if(y + h > current_mode.height) h = current_mode.height - y;
	for(uint32_t row=y; row < y+h; ++row){
		if(row > current_mode.height) break;
		for(uint32_t col=x; col < x+w; ++col){
			if(col > current_mode.width) break;
			uint32_t value;
			if(image->IsTrueColor()) {
				value=image->TrueColorPixel(col, row);
			}else{
				value=image->PalettePixel(col, row);
			}
			BufferPutPixel(col, row, value);
		}
		size_t start= GetBytePos(x, row);
		if(start > buffersize) break;
		size_t end= GetBytePos(x+w, row, true) + BytesPerPixel() + 2;
		if(end > buffersize) end=buffersize;
		
		size_t bytes = end - start;
		if(w != current_mode.width || h != current_mode.height) QueueUpdate(start, bytes, (char*)&buffer[start], hide_cursor);
	}
	if(w == current_mode.width && h == current_mode.height) {
		bt_lock(update_q_lock);
		bt_fseek(fh, 0, false);
		bt_fwrite(fh, buffersize, (char *) buffer);
		bt_unlock(update_q_lock);
	}
	//int64_t update_end = bt_rtc_millis();
	//DBG("GDS: Update took " << (update_end - update_start) << "ms");
}

void Screen::ShowCursor() {
	bt_term_ShowPointer();
	cursor_on=true;
}

void Screen::HideCursor() {
	bt_term_HidePointer();
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
			uint32_t value = img.GetTrueColorPixel(x, y);
			if(gdTrueColorGetAlpha(value) != 0) value = transparent;
			if(value != transparent){
				if(image->IsTrueColor()){
					if(pixel_conversion_required) value = ConvertPixel(value);
				}else{
					value=image->ColorClosest(gdTrueColorGetRed(value), gdTrueColorGetGreen(value), gdTrueColorGetBlue(value));
				}
			}
			
			size_t pixelpos=(y * bmp.w) + x;
			if(bmp.bpp >= 8){
				size_t depth = bmp.bpp / 8;
				size_t datapos = pixelpos * depth;
				if(datapos >= datasize) continue;
				memcpy(&data[datapos], &value, depth);
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
	bt_term_SetPointerBitmap((bt_terminal_pointer_bitmap*)complete);
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
