#include <gds/libgds.h>
#include "drawing.hpp"
#include "metrics.hpp"

using namespace std;

uint32_t titleActiveFont;
uint32_t titleInactiveFont;
uint32_t menuButtonFont;

void InitDrawing(){
	titleActiveFont = GDS_GetFontID("Resagnicto", gds_FontStyle::Bold);
	titleInactiveFont = GDS_GetFontID("Resagnicto", gds_FontStyle::Normal);
	menuButtonFont = GDS_GetFontID("Resamitz", gds_FontStyle::Bold);
}

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
	GDS_Text(x + symLength + 5, y + buttonHeight - 5, "Menu", menuButtonFont, 7, GetColour(SymbolColour));
}

uint64_t DrawTitleBar(uint32_t w, string title, bool active, WindowArea pressed){
	uint64_t ret = GDS_NewSurface(gds_SurfaceType::Bitmap, w, GetMetric(TitleBarSize));
	GDS_Box(0, 0, w, GetMetric(TitleBarSize), GetColour(SeperatorColour), active?GetColour(TitleBarColour):GetColour(InactiveTitleColour), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	DrawMenuButton(GetMetric(BorderWidth), GetMetric(BorderWidth), active, (pressed == WindowArea::MenuButton));
	uint32_t font = active ? titleActiveFont : titleInactiveFont;
	GDS_Text(GetMetric(MenuButtonWidth) + GetMetric(TitleTextMargin), GetMetric(TitleBarSize) - 4, title.c_str(), font, 9, GetColour(TitleTextColour), 0);
	DrawMaxButton(w - GetMetric(ButtonSize) - GetMetric(BorderWidth), GetMetric(BorderWidth), active, (pressed == WindowArea::ExpandButton));
	DrawMinButton(w - (GetMetric(ButtonSize) * 2) - GetMetric(BorderWidth), GetMetric(BorderWidth), active, (pressed == WindowArea::HideButton));
	DrawCloseButton(w - (GetMetric(ButtonSize) * 3) - GetMetric(BorderWidth), GetMetric(BorderWidth), active, (pressed == WindowArea::CloseButton));
	return ret;
}

void DrawBorderHorzLine(int32_t x1, int32_t y, int32_t x2, const Rect &bounds){
	if((x1 < bounds.x && x2 < bounds.x) || (x1 >= bounds.x + (int32_t)bounds.w && x2 >= bounds.x + (int32_t)bounds.w) || y < bounds.y || y > bounds.y + (int32_t)bounds.h) return;
	if(x1 > x2) swap(x1, x2);
	if(x1 < bounds.x) x1 = bounds.x;
	if(x2 > bounds.x + (int32_t)bounds.w) x2 = bounds.x + bounds.w;
	GDS_Line(x1, y, x2, y, GetColour(BorderColour), 1);
}

void DrawBorderVertLine(int32_t x, int32_t y1, int32_t y2, const Rect &bounds){
	if((y1 < bounds.y && y2 < (int32_t)bounds.y) || (y1 >= bounds.y + (int32_t)bounds.h && y2 >= bounds.y + (int32_t)bounds.h) || x < bounds.x || x > bounds.x + (int32_t)bounds.w) return;
	if(y1 > y2) swap(y1, y2);
	if(y1 < bounds.y) y1 = bounds.y;
	if(y2 > bounds.y + (int32_t)bounds.h) y2 = bounds.y + bounds.h;
	GDS_Line(x, y1, x, y2, GetColour(BorderColour), 1);
}

void DrawBorder(uint32_t x, uint32_t y, uint32_t w, uint32_t h, const Rect &bounds){
	DrawBorderHorzLine(x, y, x + w - 1, bounds);
	DrawBorderHorzLine(x, y + h - 1, x + w - 1, bounds);
	DrawBorderVertLine(x, y, y + h - 1, bounds);
	DrawBorderVertLine(x + w - 1, y, y + h - 1, bounds);
}
