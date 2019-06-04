#ifndef _FORM_HPP
#define _FORM_HPP

#include <wm/window.hpp>

#include "container.hpp"

namespace btos_api{
namespace gui{
	
class Form : public wm::Window, public Container{
private:
	gds::Rect rect;
	std::unique_ptr<gds::Surface> surf;
	
	std::shared_ptr<IControl> resizeHandle;
	
	gds::Surface &GetSurface();
	gds::Rect GetBoundingRect();

	void Update(const gds::Rect &r);
	void Update();
	void SetSubscribed(uint32_t subs);
	
	std::function<bool()> onClose;
	std::function<void(gds::Rect)> onResize;
	std::function<void()> onExpand;
	std::function<void(gds::Rect)> onMove;
	
	bool HandleEvent(const wm_Event &e);
	void CreateResizeHandle();
public:
	Form(const gds::Rect &r, uint32_t options, const std::string &title);
	
	void OnClose(std::function<bool()> oC);
	void OnResize(std::function<void(gds::Rect)> oR);
	void OnExpand(std::function<void()> oX);
	void OnMove(std::function<void(gds::Rect)> oM);
};
	
}
}

#endif
