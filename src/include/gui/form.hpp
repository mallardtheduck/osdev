#ifndef _FORM_HPP
#define _FORM_HPP

#include <wm/window.hpp>

#include "container.hpp"

namespace btos_api{
namespace gui{

namespace FormOptions{
	static const uint32_t Fixed = (wm_WindowOptions::Default | wm_WindowOptions::NoExpand);
	static const uint32_t Sizable = (wm_WindowOptions::Default | wm_WindowOptions::Resizable);
	static const uint32_t ClosedFixed = (wm_WindowOptions::Unlisted | wm_WindowOptions::NoExpand);
	static const uint32_t ClosedSizable = (wm_WindowOptions::Unlisted | wm_WindowOptions::Resizable);
}

class Form : public wm::Window, public Container{
private:
	static const auto handleSize = 18;
	bool expanded = false;
	bool enableUpdate = true;
	gds::Rect nonExpandRect;

	gds::Rect rect;
	std::unique_ptr<gds::Surface> surf;
	
	std::shared_ptr<IControl> resizeHandle;
	
	gds::Surface &GetSurface();
	gds::Rect GetBoundingRect();

	void Update(const gds::Rect &r);
	void Update();
	void SetSubscribed(uint32_t subs);
	
	std::function<bool()> onClose;
	std::function<void(const gds::Rect&)> onResize;
	std::function<void()> onExpand;
	std::function<void(const gds::Rect&)> onMove;
	
	bool HandleEvent(const wm_Event &e);
	void CreateResizeHandle();
	void PerformResize();
public:
	Form(const gds::Rect &r, uint32_t options, const std::string &title);
	
	void OnClose(std::function<bool()> oC);
	void OnResize(std::function<void(const gds::Rect&)> oR);
	void OnExpand(std::function<void()> oX);
	void OnMove(std::function<void(const gds::Rect&)> oM);
};
	
}
}

#endif
