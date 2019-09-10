#ifndef _TEXTAREA_HPP
#define _TEXTAREA_HPP

#include "icontrol.hpp"
#include "scrollbar.hpp"

namespace btos_api{
namespace gui{

class TextArea : public IValueControl<std::string>{
private:
	gds::Rect outerRect;
	gds::Rect rect; 
	std::unique_ptr<gds::Surface> bkSurf;
	
	std::function<bool(uint32_t)> onKeyPress;
	
	struct Line{
		std::string text;
		std::string measuredText;
		gds::TextMeasurements textMeasures;
		std::unique_ptr<gds::Surface> surf;
		uint64_t selSerial = 0;
		
		Line(const std::string &t) : text(t) {};
		Line() = default;
	};
	
	uint32_t fontHeight;
	
	std::vector<Line> lines;
	
	bool inSelectMode = false;
	bool haveSelection = false;
	size_t selPos = 0;
	size_t selLine = 0;
	
	size_t cursorPos = 0;
	size_t lastCursorPos = 0;
	size_t cursorLine = 0;
	size_t lastCursorLine = 0;
	
	size_t lineOffset = 0;
	size_t textOffset = 0;
	
	uint32_t textOffsetPxls = 0;
	uint32_t cursorPosPxls = 0;
	uint32_t perferredPosPxls = 0;
	uint32_t selPosPxls = 0;
	
	bool hasFocus = false;
	bool enabled = true;
	
	uint64_t selSerial = 0;
	
	std::unique_ptr<Scrollbar> hscroll;
	std::unique_ptr<Scrollbar> vscroll;
	
	gds::Rect UpdateDisplayState();
	size_t MapPosToLine(uint32_t pxlPos, const Line &line);
	void MergeLines(size_t a, size_t b);
	void SplitLine(size_t i, size_t pos);
	
	void HandleScroll(bool horiz, uint32_t v);
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
