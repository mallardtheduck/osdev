#ifndef _TEXTBOX_HPP
#define _TEXTBOX_HPP

#include "icontrol.hpp"
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

struct TextBoxImpl;
PIMPL_CLASS(TextBoxImpl);

class TextBox : public IValueControl<std::string>, public IActionControl<void>{
private:
	btos::pimpl_ptr<TextBoxImpl> im;
public:
	TextBox(const gds::Rect &r, const std::string &t = "");
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void Focus();
	void Blur();
	uint32_t GetFlags();
	void Enable();
	void Disable();
	bool IsEnabled();
	void SetPosition(const gds::Rect&);
	
	void SetText(const std::string &t);
	std::string GetText();
	std::string GetValue() {return GetText();}
	
	void OnKeyPress(const std::function<bool(uint32_t)> &oKP);
};

}
}

#endif
