#ifndef _TEXTAREA_HPP
#define _TEXTAREA_HPP

#include "icontrol.hpp"
#include "scrollbar.hpp"

#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

struct TextAreaImpl;
PIMPL_CLASS(TextAreaImpl);

class TextArea : public IValueControl<std::string>{
private:
	friend struct TextAreaImpl;

	btos::pimpl_ptr<TextAreaImpl> im;	
public:
	TextArea(const gds::Rect &r, const std::string &t, bool scrollbars = false);
	
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
	void InsertText(const std::string &text);
	std::string GetText();
	std::string GetValue() override {return GetText();}
	
	std::string GetSelection();
	void CutSelection();
	
	void OnKeyPress(const std::function<bool(uint32_t)> &oKP);
};

}
}

#endif
