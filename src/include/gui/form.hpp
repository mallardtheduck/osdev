#ifndef _FORM_HPP
#define _FORM_HPP

#include <wm/window.hpp>
#include <functional>
#include <memory>
#include <vector>

#include "icontrol.hpp"

namespace btos_api{
namespace gui{
	
class Form : public wm::Window{
private:
	std::vector<std::shared_ptr<IControl>> controls;
	std::shared_ptr<IControl> focus;
	
	bool HandleEvent(const wm_Event&);
public:
	Form(const gds::Rect &r, uint32_t options, const std::string &title);
	
	void Paint(const gds::Rect &r = gds::Rect());
	
	void AddControl(std::shared_ptr<IControl> control);
};
	
}
}

#endif
