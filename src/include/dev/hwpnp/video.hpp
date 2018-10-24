#ifndef _VIDEO_HPP
#define _VIDEO_HPP

#include "../hwpnp.hpp"
#include <btos/devices.h>
#include <dev/video_dev.h>

namespace btos_api{
namespace hwpnp{
	
	class IVideo : public IDevice{
	public:
		virtual size_t WriteFrameBuffer(size_t pos, size_t len, const uint8_t *buf) = 0;
		virtual size_t ReadFrameBuffer(size_t pos, size_t len, uint8_t *buf) = 0;
		
		virtual size_t GetModeCount() = 0;
		virtual bt_vidmode GetMode(size_t idx) = 0;
		virtual void SetMode(const bt_vidmode &mode) = 0;
		virtual bt_vidmode QueryMode() = 0;
		virtual bt_video_palette_entry GetPaletteEntry(uint8_t idx) = 0;
		
		virtual void SetTextColours(uint8_t c) = 0;
		virtual uint8_t GetTextColours() = 0;
		virtual bool GetScrolling() = 0;
		virtual void SetScrolling(bool v) = 0;
		virtual bool GetCursorVisibility() = 0;
		virtual void SetCursorVisibility(bool v) = 0;
		
		virtual void ClearScreen() = 0;
		
		int GetType() {
			return driver_types::VIDEO;
		}
		
		virtual ~IVideo() {}
	};
	
}
}

#endif