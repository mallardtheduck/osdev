#ifndef _SCREEN_HPP
#define _SCREEN_HPP

#include "surface.hpp"
#include "geom.hpp"
#include <dev/video_dev.h>

namespace btos_api{
namespace gds{

	class Screen : public Surface{
	private:
		Screen() {}
	public:
		static Screen Get();
		void Select();

		void Update();
		void Update(const Rect &r);
		void SetMode(bt_vidmode mode);
		void SetCursor(const Surface &surf, const Point &hotspot);

		void SetCursorVisibility(bool state);
		bool GetCursorVisibility();
	};

}
}

#endif
