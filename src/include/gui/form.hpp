#ifndef _FORM_HPP
#define _FORM_HPP

#include <wm/window.hpp>
#include <functional>
#include <memory>
#include <vector>

#include "container.hpp"

namespace btos_api{
namespace gui{
	
class Form : public wm::Window, public Container{
private:
	gds::Rect rect;
	gds::Surface surf;
	
	gds::Surface &GetSurface();
	gds::Rect GetBoundingRect();

	void Update(const gds::Rect &r);
	void Update();
	void SetSubscribed(uint32_t subs);
public:
	Form(const gds::Rect &r, uint32_t options, const std::string &title);
};
	
}
}

#endif
