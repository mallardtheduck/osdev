#ifndef _FORM_HPP
#define _FORM_HPP

#include <wm/window.hpp>
#include <util/pimpl_ptr.hpp>

#include "container.hpp"

namespace btos_api{
namespace gui{

namespace FormOptions{
	static const uint32_t Fixed = (wm_WindowOptions::Default | wm_WindowOptions::NoExpand);
	static const uint32_t Sizable = (wm_WindowOptions::Default | wm_WindowOptions::Resizable);
	static const uint32_t ClosedFixed = (wm_WindowOptions::Unlisted | wm_WindowOptions::NoExpand);
	static const uint32_t ClosedSizable = (wm_WindowOptions::Unlisted | wm_WindowOptions::Resizable);
}

struct FormImpl;
PIMPL_CLASS(FormImpl);

class Form : public wm::Window, public Container{
private:
	btos::pimpl_ptr<FormImpl> im;
	friend struct FormImpl;

	gds::Surface &GetSurface();
	gds::Rect GetBoundingRect();

	void Update(const gds::Rect &r);
	void Update();
	void SetSubscribed(uint32_t subs);
public:
	Form(const gds::Rect &r, uint32_t options, const std::string &title);
	
	void OnClose(std::function<bool()> oC);
	void OnResize(std::function<void(const gds::Rect&)> oR);
	void OnExpand(std::function<void()> oX);
	void OnMove(std::function<void(const gds::Rect&)> oM);
	void OnGlobal(std::function<void(const wm_Event &e)> oG);
	
	void Resize(uint32_t w, uint32_t h);
};
	
}
}

#endif
