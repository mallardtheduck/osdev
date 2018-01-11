#ifndef _SCREEN_HPP
#define _SCREEN_HPP

#include "surface.hpp"
#include "geom.hpp"
#include <dev/video_dev.h>

namespace btos_api{
namespace gds{

	class ScreenClass : public Surface{
	private:
		ScreenClass() {}
	public:
		static ScreenClass Get();
		void Select() const override;

		void Update();
		void Update(const Rect &r);
		void SetMode(bt_vidmode mode);
		void SetCursor(const Surface &surf, const Point &hotspot);

		void SetCursorVisibility(bool state);
		bool GetCursorVisibility();
	};
	
	extern ScreenClass Screen;

}
}

#endif
