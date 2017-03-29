#include <gds/libgds.h>
#include "drawing.hpp"
#include "metrics.hpp"

using namespace std;

uint32_t titleActiveFont;
uint32_t titleInactiveFont;
uint32_t menuButtonFont;

void InitDrawing(){
	titleActiveFont = GDS_GetFontID(GetSetting(TitleFontName).c_str(), gds_FontStyle::Bold);
	titleInactiveFont = GDS_GetFontID(GetSetting(TitleFontName).c_str(), gds_FontStyle::Normal);
	menuButtonFont = GDS_GetFontID(GetSetting(MenuButtonFontName).c_str(), gds_FontStyle::Bold);
}

static uint32_t buttonHighlightColour, buttonFaceColour, buttonShadowColour, borderColour, lineColour, titleBarColour, inactiveTitleColour;
static uint32_t seperatorColour, titleTextColour, symbolColour;

static void DrawButtonUp(uint32_t x, uint32_t y, uint32_t w, uint32_t h, bool active){
	vector<gds_DrawingOp> ops;
	ops.push_back(GDS_Box_Op(x+1, y+1, w-1, h-1, buttonHighlightColour, buttonFaceColour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled));
	ops.push_back(GDS_Line_Op(x+1, y+h-2, x+w-2, y+h-2, buttonShadowColour, 1));
	ops.push_back(GDS_Line_Op(x+w-2, y+h-1, x+w-2, y+2, buttonShadowColour, 1));
	ops.push_back(GDS_Box_Op(x, y, w, h, lineColour, borderColour, 1));
	ops.push_back(GDS_Dot_Op(x, y, active?titleBarColour:inactiveTitleColour, 1));
	ops.push_back(GDS_Dot_Op(x+w-1, y, active?titleBarColour:inactiveTitleColour, 1));
	ops.push_back(GDS_Dot_Op(x, y+h-1, active?titleBarColour:inactiveTitleColour, 1));
	ops.push_back(GDS_Dot_Op(x+w-1, y+h-1, active?titleBarColour:inactiveTitleColour, 1));
	GDS_MultiDrawingOps(ops.size(), &ops[0], NULL);
}

static void DrawButtonDown(uint32_t x, uint32_t y, uint32_t w, uint32_t h, bool active){
	vector<gds_DrawingOp> ops;
	ops.push_back(GDS_Box_Op(x+1, y+1, w-1, h-1, buttonShadowColour, buttonFaceColour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled));
	ops.push_back(GDS_Line_Op(x+1, y+h-2, x+w-2, y+h-2, buttonHighlightColour, 1));
	ops.push_back(GDS_Line_Op(x+w-2, y+h-1, x+w-2, y+2, buttonHighlightColour, 1));
	ops.push_back(GDS_Box_Op(x, y, w, h, lineColour, borderColour, 1));
	ops.push_back(GDS_Dot_Op(x, y, active?titleBarColour:inactiveTitleColour, 1));
	ops.push_back(GDS_Dot_Op(x+w-1, y, active?titleBarColour:inactiveTitleColour, 1));
	ops.push_back(GDS_Dot_Op(x, y+h-1, active?titleBarColour:inactiveTitleColour, 1));
	ops.push_back(GDS_Dot_Op(x+w-1, y+h-1, active?titleBarColour:inactiveTitleColour, 1));
	GDS_MultiDrawingOps(ops.size(), &ops[0], NULL);
}

static void DrawMaxButton(uint32_t x, uint32_t y, bool active, bool down = false){
	uint32_t buttonSize = GetMetric(TitleBarSize)-2;
	if(down) DrawButtonDown(x, y, buttonSize, buttonSize, active);
	else DrawButtonUp(x, y, buttonSize, buttonSize, active);
	uint32_t borderWidth = buttonSize / 4;
	GDS_Box(x + borderWidth, y + borderWidth, buttonSize - (2*borderWidth), buttonSize - (2*borderWidth), symbolColour, 0, 2);
}

static void DrawMinButton(uint32_t x, uint32_t y, bool active, bool down = false){
	uint32_t buttonSize = GetMetric(ButtonSize);
	if(down) DrawButtonDown(x, y, buttonSize, buttonSize, active);
	else DrawButtonUp(x, y, buttonSize, buttonSize, active);
	uint32_t symbolSize = buttonSize / 4;
	uint32_t borderWidth = (buttonSize - symbolSize) / 2;
	GDS_Box(x + borderWidth, y + borderWidth, buttonSize - (2*borderWidth), buttonSize - (2*borderWidth), 0, symbolColour, 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
}

static void DrawCloseButton(uint32_t x, uint32_t y, bool active, bool down = false){
	uint32_t buttonSize = GetMetric(ButtonSize);
	if(down) DrawButtonDown(x, y, buttonSize, buttonSize, active);
	else DrawButtonUp(x, y, buttonSize, buttonSize, active);
	uint32_t half = buttonSize / 2;
	uint32_t quarter = buttonSize / 4;
	vector<gds_DrawingOp> ops;
	ops.push_back(GDS_Line_Op(x + quarter, y + quarter, x + half, y + half, symbolColour, 2));
	ops.push_back(GDS_Line_Op(x + (buttonSize - quarter) - 1, y + quarter, x + half - 1, y + half, symbolColour, 2));
	ops.push_back(GDS_Line_Op(x + quarter, y + (buttonSize - quarter) - 1, x + half, y + half - 1, symbolColour, 2));
	ops.push_back(GDS_Line_Op(x + (buttonSize - quarter) - 1, y + (buttonSize - quarter) - 1, x + half - 1, y + half - 1, symbolColour, 2));
	GDS_MultiDrawingOps(ops.size(), &ops[0], NULL);
}

static void DrawMenuButton(uint32_t x, uint32_t y, bool active, bool down = false){
	uint32_t buttonHeight = GetMetric(ButtonSize);
	uint32_t buttonWidth = GetMetric(MenuButtonWidth);
	if(down) DrawButtonDown(x, y, buttonWidth, buttonHeight, active);
	else DrawButtonUp(x, y, buttonWidth, buttonHeight, active);
	uint32_t borderWidth = buttonHeight / 4;
	uint32_t symLength = buttonHeight - borderWidth;
	vector<gds_DrawingOp> ops;
	ops.push_back(GDS_Line_Op(x + borderWidth, y + borderWidth, x + symLength, y + borderWidth, symbolColour, 2));
	ops.push_back(GDS_Line_Op(x + borderWidth, y + (buttonHeight / 2), x + symLength, y + (buttonHeight / 2), symbolColour, 2));
	ops.push_back(GDS_Line_Op(x + borderWidth, y + buttonHeight - borderWidth, x + symLength, y + buttonHeight - borderWidth, symbolColour, 2));
	GDS_MultiDrawingOps(ops.size(), &ops[0], NULL);
	GDS_Text(x + symLength + 5, y + buttonHeight - 5, "Menu", menuButtonFont, GetMetric(MenuButtonFontSize), symbolColour);
}

uint64_t DrawTitleBar(uint32_t w, string title, bool active, WindowArea pressed){
	uint64_t ret = GDS_NewSurface(gds_SurfaceType::Bitmap, w, GetMetric(TitleBarSize));
	
	buttonHighlightColour = GetColour(ButtonHighlightColour);
	buttonFaceColour = GetColour(ButtonFaceColour);
	buttonShadowColour = GetColour(ButtonShadowColour);
	borderColour = GetColour(BorderColour); 
	lineColour = GetColour(LineColour); 
	titleBarColour = GetColour(TitleBarColour);
	inactiveTitleColour = GetColour(InactiveTitleColour);
	seperatorColour = GetColour(SeperatorColour);
	titleTextColour = GetColour(TitleTextColour);
	symbolColour = GetColour(SymbolColour);
	
	GDS_Box(0, 0, w, GetMetric(TitleBarSize), seperatorColour, active?titleBarColour:inactiveTitleColour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	DrawMenuButton(GetMetric(BorderWidth), GetMetric(BorderWidth), active, (pressed == WindowArea::MenuButton));
	uint32_t font = active ? titleActiveFont : titleInactiveFont;
	GDS_Text(GetMetric(MenuButtonWidth) + GetMetric(TitleTextMargin), GetMetric(TitleBarSize) - GetMetric(TitleTextBaseline), title.c_str(), font, GetMetric(TitleFontSize), titleTextColour, 0);
	DrawMaxButton(w - GetMetric(ButtonSize) - GetMetric(BorderWidth), GetMetric(BorderWidth), active, (pressed == WindowArea::ExpandButton));
	DrawMinButton(w - (GetMetric(ButtonSize) * 2) - GetMetric(BorderWidth), GetMetric(BorderWidth), active, (pressed == WindowArea::HideButton));
	DrawCloseButton(w - (GetMetric(ButtonSize) * 3) - GetMetric(BorderWidth), GetMetric(BorderWidth), active, (pressed == WindowArea::CloseButton));
	return ret;
}

static void DrawBorderHorzLine(int32_t x1, int32_t y, int32_t x2, const Rect &bounds){
	if((x1 < bounds.x && x2 < bounds.x) || (x1 >= bounds.x + (int32_t)bounds.w && x2 >= bounds.x + (int32_t)bounds.w) || y < bounds.y || y > bounds.y + (int32_t)bounds.h) return;
	if(x1 > x2) swap(x1, x2);
	if(x1 < bounds.x) x1 = bounds.x;
	if(x2 > bounds.x + (int32_t)bounds.w) x2 = bounds.x + bounds.w;
	GDS_Line(x1, y, x2, y, borderColour, 1);
}

static void DrawBorderVertLine(int32_t x, int32_t y1, int32_t y2, const Rect &bounds){
	if((y1 < bounds.y && y2 < (int32_t)bounds.y) || (y1 >= bounds.y + (int32_t)bounds.h && y2 >= bounds.y + (int32_t)bounds.h) || x < bounds.x || x > bounds.x + (int32_t)bounds.w) return;
	if(y1 > y2) swap(y1, y2);
	if(y1 < bounds.y) y1 = bounds.y;
	if(y2 > bounds.y + (int32_t)bounds.h) y2 = bounds.y + bounds.h;
	GDS_Line(x, y1, x, y2, borderColour, 1);
}

void DrawBorder(uint32_t x, uint32_t y, uint32_t w, uint32_t h, const Rect &bounds){
	borderColour = GetColour(BorderColour);
	DrawBorderHorzLine(x, y, x + w - 1, bounds);
	DrawBorderHorzLine(x, y + h - 1, x + w - 1, bounds);
	DrawBorderVertLine(x, y, y + h - 1, bounds);
	DrawBorderVertLine(x + w - 1, y, y + h - 1, bounds);
}
