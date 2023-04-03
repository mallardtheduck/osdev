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
	void InsertText(const std::string &text);
	std::string GetText();
	std::string GetValue() {return GetText();}
	
	std::string GetSelection();
	void CutSelection();
	
	void OnKeyPress(const std::function<bool(uint32_t)> &oKP);
};

}
}

#endif
