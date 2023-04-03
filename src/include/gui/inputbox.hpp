#ifndef _INPUTBOX_HPP
#define _INPUTBOX_HPP

#include <wm/window.hpp>
#include <gds/surface.hpp>

#include <memory>
#include <string>

#include <gui/idialog.hpp>
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

struct InputBoxImpl;
PIMPL_CLASS(InputBoxImpl);

class InputBox : public IDialog<std::string>{
private:
	btos::pimpl_ptr<InputBoxImpl> im;
public:
	InputBox();
	InputBox(const std::string &message, const std::string &title, const std::string &defvalue = "", std::shared_ptr<gds::Surface> icon = nullptr);
	
	std::string Show(wm::Window *parent) override;
	
	void SetMessage(const std::string &msg);
	void SetTitle(const std::string &title);
	void SetIcon(std::shared_ptr<gds::Surface> icon);
};

}
}

#endif