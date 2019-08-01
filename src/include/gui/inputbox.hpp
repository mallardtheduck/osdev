#ifndef _INPUTBOX_HPP
#define _INPUTBOX_HPP

#include <wm/window.hpp>
#include <gds/surface.hpp>

#include <memory>
#include <string>

#include <gui/idialog.hpp>

namespace btos_api{
namespace gui{

class InputBox : public IDialog<std::string>{
private:
	std::string message;
	std::string title;
	std::string defvalue;
	std::shared_ptr<gds::Surface> icon;
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