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
	
	EventResponse HandleEvent(const wm_Event&) override;
	void Paint(gds::Surface &surf) override;
	gds::Rect GetPaintRect() override;
	gds::Rect GetInteractRect() override;
	uint32_t GetSubscribed() override;
	void Focus() override;
	void Blur() override;
	uint32_t GetFlags() override;
	void Enable() override;
	void Disable() override;
	bool IsEnabled() override;
	void SetPosition(const gds::Rect&) override;
	
	void SetText(const std::string &t);
	std::string GetText();
	std::string GetValue() override {return GetText();}
	
	void OnKeyPress(const std::function<bool(uint32_t)> &oKP);
};

}
}

#endif
