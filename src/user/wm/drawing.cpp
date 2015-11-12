#include <gds/libgds.h>
#include "drawing.hpp"
#include "metrics.hpp"

using namespace std;

void DrawButtonUp(uint32_t x, uint32_t y, uint32_t w, uint32_t h, bool active){
	GDS_Box(x+1, y+1, w-1, h-1, GetColour(ButtonHighlightColour), GetColour(ButtonFaceColour), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	GDS_Line(x+1, y+h-2, x+w-2, y+h-2, GetColour(ButtonShadowColour), 1);
	GDS_Line(x+w-2, y+h-1, x+w-2, y+2, GetColour(ButtonShadowColour), 1);
	GDS_Box(x, y, w, h, GetColour(LineColour), GetColour(BorderColour), 1);
	GDS_Dot(x, y, active?GetColour(TitleBarColour):GetColour(InactiveTitleColour), 1);
	GDS_Dot(x+w-1, y, active?GetColour(TitleBarColour):GetColour(InactiveTitleColour), 1);
	GDS_Dot(x, y+h-1, active?GetColour(TitleBarColour):GetColour(InactiveTitleColour), 1);
	GDS_Dot(x+w-1, y+h-1, active?GetColour(TitleBarColour):GetColour(InactiveTitleColour), 1);
}

void DrawButtonDown(uint32_t x, uint32_t y, uint32_t w, uint32_t h, bool active){
	GDS_Box(x+1, y+1, w-1, h-1, GetColour(ButtonShadowColour), GetColour(ButtonFaceColour), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	GDS_Line(x+1, y+h-2, x+w-2, y+h-2, GetColour(ButtonHighlightColour), 1);
	GDS_Line(x+w-2, y+h-1, x+w-2, y+2, GetColour(ButtonHighlightColour), 1);
	GDS_Box(x, y, w, h, GetColour(LineColour), GetColour(BorderColour), 1);
	GDS_Dot(x, y, active?GetColour(TitleBarColour):GetColour(InactiveTitleColour), 1);
	GDS_Dot(x+w-1, y, active?GetColour(TitleBarColour):GetColour(InactiveTitleColour), 1);
	GDS_Dot(x, y+h-1, active?GetColour(TitleBarColour):GetColour(InactiveTitleColour), 1);
	GDS_Dot(x+w-1, y+h-1, active?GetColour(TitleBarColour):GetColour(InactiveTitleColour), 1);
}

void DrawMaxButton(uint32_t x, uint32_t y, bool active, bool down = false){
	uint32_t buttonSize = GetMetric(TitleBarSize)-2;
	if(down) DrawButtonDown(x, y, buttonSize, buttonSize, active);
	else DrawButtonUp(x, y, buttonSize, buttonSize, active);
	uint32_t borderWidth = buttonSize / 4;
	GDS_Box(x + borderWidth, y + borderWidth, buttonSize - (2*borderWidth), buttonSize - (2*borderWidth), GetColour(SymbolColour), 0, 2);
}

void DrawMinButton(uint32_t x, uint32_t y, bool active, bool down = false){
	uint32_t buttonSize = GetMetric(ButtonSize);
	if(down) DrawButtonDown(x, y, buttonSize, buttonSize, active);
	else DrawButtonUp(x, y, buttonSize, buttonSize, active);
	uint32_t symbolSize = buttonSize / 4;
	uint32_t borderWidth = (buttonSize - symbolSize) / 2;
	GDS_Box(x + borderWidth, y + borderWidth, buttonSize - (2*borderWidth), buttonSize - (2*borderWidth), 0, GetColour(SymbolColour), 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
}

void DrawCloseButton(uint32_t x, uint32_t y, bool active, bool down = false){
	uint32_t buttonSize = GetMetric(ButtonSize);
	if(down) DrawButtonDown(x, y, buttonSize, buttonSize, active);
	else DrawButtonUp(x, y, buttonSize, buttonSize, active);
	uint32_t half = buttonSize / 2;
	uint32_t quarter = buttonSize / 4;
	GDS_Line(x + quarter, y + quarter, x + half, y + half, GetColour(SymbolColour), 2);
	GDS_Line(x + (buttonSize - quarter) - 1, y + quarter, x + half - 1, y + half, GetColour(SymbolColour), 2);
	GDS_Line(x + quarter, y + (buttonSize - quarter) - 1, x + half, y + half - 1, GetColour(SymbolColour), 2);
	GDS_Line(x + (buttonSize - quarter) - 1, y + (buttonSize - quarter) - 1, x + half - 1, y + half - 1, GetColour(SymbolColour), 2);
}

void DrawMenuButton(uint32_t x, uint32_t y, bool active, bool down = false){
	uint32_t buttonHeight = GetMetric(ButtonSize);
	uint32_t buttonWidth = GetMetric(MenuButtonWidth);
	if(down) DrawButtonDown(x, y, buttonWidth, buttonHeight, active);
	else DrawButtonUp(x, y, buttonWidth, buttonHeight, active);
	uint32_t borderWidth = buttonHeight / 4;
	uint32_t symLength = buttonHeight - borderWidth;
	GDS_Line(x + borderWidth, y + borderWidth, x + symLength, y + borderWidth, GetColour(SymbolColour), 2);
	GDS_Line(x + borderWidth, y + (buttonHeight / 2), x + symLength, y + (buttonHeight / 2), GetColour(SymbolColour), 2);
	GDS_Line(x + borderWidth, y + buttonHeight - borderWidth, x + symLength, y + buttonHeight - borderWidth, GetColour(SymbolColour), 2);
	GDS_Text(x + symLength + 5, y + 2, "Menu", 0, 0, GetColour(SymbolColour));
}

void DrawTitleBar(uint32_t x, uint32_t y, uint32_t w, string title, bool active, WindowArea pressed){
	GDS_Box(x, y, w, GetMetric(TitleBarSize), GetColour(SeperatorColour), active?GetColour(TitleBarColour):GetColour(InactiveTitleColour), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	DrawMenuButton(x + GetMetric(BorderWidth), y + GetMetric(BorderWidth), active, (pressed == WindowArea::MenuButton));
	DrawMaxButton(x + w - GetMetric(ButtonSize) - GetMetric(BorderWidth), y+GetMetric(BorderWidth), active, (pressed == WindowArea::MaxButton));
	DrawMinButton(x + w - (GetMetric(ButtonSize) * 2) - GetMetric(BorderWidth), y+GetMetric(BorderWidth), active, (pressed == WindowArea::MinButton));
	DrawCloseButton(x + w - (GetMetric(ButtonSize) * 3) - GetMetric(BorderWidth), y+GetMetric(BorderWidth), active, (pressed == WindowArea::CloseButton));
	GDS_Text(x+55, y+3, title.c_str(), 0, 0, GetColour(TitleTextColour), 0);
}

void DrawBorder(uint32_t x, uint32_t y, uint32_t w, uint32_t h){
	GDS_Box(x, y, w, h, GetColour(BorderColour), 1);
}