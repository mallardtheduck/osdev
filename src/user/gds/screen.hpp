#ifndef _SCREEN_HPP
#define _SCREEN_HPP

#include "gds.hpp"
#include "bitmap_surface.hpp"

class Screen : public BitmapSurface{
private:
	bt_vidmode original_mode, current_mode;
	bt_filehandle fh;
	uint8_t *buffer;
	size_t buffersize;
	bool cursor_on;
	bt_terminal_pointer_bitmap cursor_bmp_info;

private:

	void BufferPutPixel(uint32_t x, uint32_t y, uint32_t value);
	uint32_t BufferGetPixel(uint32_t x, uint32_t y);
	size_t GetBytePos(uint32_t x, uint32_t y, bool upper = false);
	size_t BytesPerPixel();

public:
	Screen();
	~Screen();

	bool SetMode(uint32_t w, uint32_t h, uint8_t bpp);

	void UpdateScreen(uint32_t x=0, uint32_t y=0, uint32_t w=0, uint32_t h=0);
	void ShowCursor();
	void HideCursor();
	void SetCursorImage(const GD::Image &img, uint32_t hotx, uint32_t hoty);
	void RestoreMode();
	
	gds_SurfaceType::Enum GetType() override;
};

std::shared_ptr<Screen> GetScreen();

#endif