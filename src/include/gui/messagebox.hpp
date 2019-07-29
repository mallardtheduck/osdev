#ifndef _MESSAGEBOX_HPP
#define _MESSAGEBOX_HPP

#include <wm/window.hpp>
#include <gds/surface.hpp>

#include <memory>
#include <string>

namespace btos_api{
namespace gui{

class MessageBox{
private:
	std::string message;
	std::string title;
	std::shared_ptr<gds::Surface> icon;
	std::vector<std::string> buttons;
public:
	MessageBox();
	MessageBox(const std::string &message, const std::string &title, std::shared_ptr<gds::Surface> icon = nullptr, std::vector<std::string> buttons = {"OK"});
	
	size_t Show(wm::Window *parent);
	
	void SetMessage(const std::string &msg);
	void SetTitle(const std::string &title);
	void SetIcon(std::shared_ptr<gds::Surface> icon);
	void SetButons(std::vector<std::string> buttons);
};

}
}

#endif