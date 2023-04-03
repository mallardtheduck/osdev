#include <gui/textbox.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>
#include <dev/keyboard.h>

#include <iostream>
#include <cmath>

namespace btos_api{
namespace gui{

struct TextBoxImpl{
	gds::Rect rect;
	std::string text;
	std::unique_ptr<gds::Surface> surf;
	
	std::function<bool(uint32_t)> onKeyPress;
	
	gds::TextMeasurements textMeasures;
	
	bool update = false;
	size_t textOffset = 0;
	size_t cursorPos = 0;
	bool hasFocus = false;
	bool enabled = true;
	int32_t textY = 0;
	
	void UpdateDisplayState();
};
PIMPL_IMPL(TextBoxImpl);

TextBox::TextBox(const gds::Rect &r, const std::string &t) : im(new TextBoxImpl()){
	im->rect = r; im->text = t;
}
	
void TextBoxImpl::UpdateDisplayState(){
	if(!surf){
		surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		update = true;
	}
	
	if(textMeasures.w == 0 || update) textMeasures = surf->MeasureText(text, fonts::GetTextBoxFont(), fonts::GetTextBoxTextSize());
	textY = std::max<int32_t>(((rect.h + textMeasures.h) / 2), 0);
	
	size_t vchars;
	while(true){
		auto textW = rect.w - 5;
		
		vchars = 0;
		double cWidth = 0.0;
		bool overflow = false;
		bool underflow = false;
		
		for(size_t i = 0; i < textMeasures.charX.size(); ++i){
			if(i >= textOffset){
				++vchars;
				cWidth += textMeasures.charX[i];
				if(cWidth > textW){
					overflow = true;
					break;
				}
			}else{
				underflow = true;
			}
		}
		
		if(overflow && cursorPos > textOffset + std::max<int32_t>((int32_t)vchars - 2, 0)){
			++textOffset;
			update = true;
			if(textOffset >= text.length()) break;
		}else if(underflow && cursorPos < textOffset + 1){
			--textOffset;
			update = true;
		}else if(textOffset > text.length()){
			--textOffset;
			update = true;
		}else break;
	}
	//std::cout << "UpdateDisplayState: cursorPos: " << cursorPos << " textOffset: " << textOffset << " text.length():" << text.length() << std::endl;//
}
	
EventResponse TextBox::HandleEvent(const wm_Event &e){
	bool updateCursor = false;
	bool handled = false;
	if(e.type == wm_EventType::Keyboard && !(e.Key.code & KeyFlags::KeyUp)){
		uint16_t code = KB_code(e.Key.code);
		if(im->onKeyPress){
			if(im->onKeyPress(e.Key.code)) handled = true;
		}
		if(!handled){
			if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow) && im->cursorPos > 0){
				--im->cursorPos;
				updateCursor = true;
				handled = true;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow) && im->cursorPos < im->text.length()){
				++im->cursorPos;
				updateCursor = true;
				handled = true;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::Delete) && im->cursorPos <= im->text.length()){
				im->text.erase(im->cursorPos, 1);
				RaiseChangeEvent();
				if(im->cursorPos > im->text.length()) im->cursorPos = im->text.length();
				im->update = true;
				handled = true;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::Home)){
				im->cursorPos = 0;
				updateCursor = true;
				handled = true;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::End)){
				im->cursorPos = im->text.length();
				updateCursor = true;
				handled = true;
			}else if(!(code & KeyFlags::NonASCII)){
				char c = KB_char(e.Key.code);
				auto preText = im->text;
				if(c == 0x08 && im->cursorPos > 0){
					im->text.erase(im->cursorPos - 1, 1);
					RaiseChangeEvent();
					--im->cursorPos;
					handled = true;
				}else if(c == '\n'){
					RaiseActionEvent();
				}else if(c > 31){
					im->text.insert(im->cursorPos, 1, c);
					RaiseChangeEvent();
					++im->cursorPos;
					handled = true;
				}
				im->update = (preText != im->text);
			}
		}
	}else if(e.type == wm_EventType::PointerButtonDown || e.type == wm_EventType::PointerButtonUp){
		handled = true;
		auto pointerX = e.Pointer.x - im->rect.x;
		double xpos = 0.5;
		auto newCursorPos = im->cursorPos;
		for(size_t i = im->textOffset; i < im->textMeasures.charX.size(); ++i){
			xpos += im->textMeasures.charX[i];
			if(xpos > pointerX){
				newCursorPos = i;
				break;
			}else{
				newCursorPos = i + 1;
			}
		}
		if(newCursorPos != im->cursorPos){
			im->cursorPos = newCursorPos;
			updateCursor = true;
		}
	}
	
	
	if(im->update || updateCursor) IControl::Paint(im->rect);
	return {handled};
}

void TextBox::Paint(gds::Surface &s){
	im->UpdateDisplayState();
	
	if(im->update){
		uint32_t inW = im->rect.w - 1;
		uint32_t inH = im->rect.h - 1;
		
		auto bkgCol = colours::GetBackground().Fix(*im->surf);
		auto txtCol = colours::GetTextBoxText().Fix(*im->surf);
		auto border = colours::GetBorder().Fix(*im->surf);
		
		im->surf->Clear();
		
		im->surf->BeginQueue();
		im->surf->Box(im->rect.AtZero(), bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		if(im->textOffset < im->text.length()) im->surf->Text({2, im->textY}, im->text.substr(im->textOffset), fonts::GetTextBoxFont(), fonts::GetTextBoxTextSize(), txtCol);
		drawing::Border(*im->surf, {0, 0, inW, inH}, border);
		
		auto topLeft = colours::GetTextBoxLowLight().Fix(*im->surf);
		auto bottomRight = colours::GetTextBoxHiLight().Fix(*im->surf);
		drawing::BevelBox(*im->surf, {1, 1, inW - 2, inH - 2}, topLeft, bottomRight);

		im->surf->CommitQueue();
		im->update = false;
	}
	
	s.Blit(*im->surf, im->rect.AtZero(), im->rect);
	
	if(im->hasFocus){
		auto cursorCol = colours::GetTextCursor().Fix(*im->surf);
		
		double cursorXd = 1.5;
		for(size_t i = im->textOffset; i < im->cursorPos && i <im-> textMeasures.charX.size(); ++i){
			cursorXd += im->textMeasures.charX[i];
		}
		if(cursorXd == 1.5 && im->text.length() == 1 && im->cursorPos == 1) cursorXd = im->textMeasures.w;
		int32_t cursorX = round(cursorXd);
		s.Line({(int32_t)cursorX + im->rect.x, (int32_t)2 + im->rect.y}, {(int32_t)cursorX + im->rect.x, (int32_t)(im->rect.h - 3) + im->rect.y}, cursorCol);
	}
	
	if(!im->enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(im->rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect TextBox::GetPaintRect(){
	return im->rect;
}

gds::Rect TextBox::GetInteractRect(){
	return im->rect;
}

uint32_t TextBox::GetSubscribed(){
	return wm_KeyboardEvents | wm_EventType::PointerButtonUp | wm_EventType::PointerButtonDown;
}

void TextBox::Focus(){
	im->hasFocus = true;
	IControl::Paint(im->rect);
}

void TextBox::Blur(){
	im->hasFocus = false;
	IControl::Paint(im->rect);
}
	
void TextBox::SetText(const std::string &t){
	im->text = t;
	im->cursorPos = 0;
	im->update = true;
	IControl::Paint(im->rect);
}

std::string TextBox::GetText(){
	return im->text;
}

void TextBox::OnKeyPress(const std::function<bool(uint32_t)> &oKP){
	im->onKeyPress = oKP;
}

uint32_t TextBox::GetFlags(){
	return 0;
}

void TextBox::Enable(){
	if(!im->enabled){
		im->enabled = true;
		IControl::Paint(im->rect);
	}
}

void TextBox::Disable(){
	if(im->enabled){
		im->enabled = false;
		IControl::Paint(im->rect);
	}
}

bool TextBox::IsEnabled(){
	return im->enabled;
}

void TextBox::SetPosition(const gds::Rect &r){
	im->rect = r;
	im->update = true;
	im->surf.reset();
}

}
}
