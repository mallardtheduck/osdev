#ifndef _MESSAGEBOX_HPP
#define _MESSAGEBOX_HPP

#include <wm/window.hpp>
#include <gds/surface.hpp>

#include <memory>
#include <string>

#include <gui/idialog.hpp>
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

struct MessageBoxImpl;
PIMPL_CLASS(MessageBoxImpl);

class MessageBox : public IDialog<size_t>{
private:
	btos::pimpl_ptr<MessageBoxImpl> im;
public:
	MessageBox();
	MessageBox(const std::string &message, const std::string &title, std::shared_ptr<gds::Surface> icon = nullptr, std::vector<std::string> buttons = {"OK"});
	
	size_t Show(wm::Window *parent) override;
	
	void SetMessage(const std::string &msg);
	void SetTitle(const std::string &title);
	void SetIcon(std::shared_ptr<gds::Surface> icon);
	void SetButons(std::vector<std::string> buttons);
};

}
}

#endif