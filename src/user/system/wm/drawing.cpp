#include <gds/libgds.h>
#include "drawing.hpp"
#include "metrics.hpp"
#include <utility>
#include <wm/wm.h>
#include <sstream>
#include <btos.h>

#define DBG(x) do{std::stringstream dbgss; dbgss << x << std::endl; bt_zero(dbgss.str().c_str());}while(0)

using namespace std;

static uint32_t titleActiveFont;
static uint32_t titleInactiveFont;
static uint32_t menuButtonFont;
static uint32_t menuFont;

void InitDrawing(){
	titleActiveFont = GDS_GetFontID(GetSetting(TitleFontName).c_str(), gds_FontStyle::Bold);
	titleInactiveFont = GDS_GetFontID(GetSetting(TitleFontName).c_str(), gds_FontStyle::Normal);
	menuButtonFont = GDS_GetFontID(GetSetting(MenuButtonFontName).c_str(), gds_FontStyle::Bold);
	menuFont = GDS_GetFontID(GetSetting(MenuFontName).c_str(), gds_FontStyle::Bold);
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

uint64_t TitleBar::Draw(uint32_t w, const string &t, bool active, WindowArea p){
	uint64_t ret;
	bool drawAll = false;
	if(w != width){
		if(gds_active_title){
			GDS_SelectSurface(gds_active_title);
			GDS_DeleteSurface();
		}
		if(gds_inactive_title){
			GDS_SelectSurface(gds_inactive_title);
			GDS_DeleteSurface();
		}
	}
	if((active && !gds_active_title) || (!active && !gds_inactive_title)){
		ret = GDS_NewSurface(gds_SurfaceType::Bitmap, w, GetMetric(TitleBarSize));
		drawAll = true;
	}else{
		if(active) ret = gds_active_title;
		else ret = gds_inactive_title;
		GDS_SelectSurface(ret);
	}
	if(t != title) drawAll = true;
	
	if(drawAll || p != pressed){
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
	}
	
	if(drawAll) GDS_Box(0, 0, w, GetMetric(TitleBarSize), seperatorColour, active?titleBarColour:inactiveTitleColour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	if(drawAll || (p != pressed && (p == WindowArea::MenuButton || pressed == WindowArea::MenuButton))){
		DrawMenuButton(GetMetric(BorderWidth), GetMetric(BorderWidth), active, (p == WindowArea::MenuButton));
	}
	if(drawAll){
		uint32_t font = active ? titleActiveFont : titleInactiveFont;
		GDS_Text(GetMetric(MenuButtonWidth) + GetMetric(TitleTextMargin), GetMetric(TitleBarSize) - GetMetric(TitleTextBaseline), t.c_str(), font, GetMetric(TitleFontSize), titleTextColour, 0);
	}
	if(drawAll || (p != pressed && (p == WindowArea::ExpandButton || pressed == WindowArea::ExpandButton))){
		DrawMaxButton(w - GetMetric(ButtonSize) - GetMetric(BorderWidth), GetMetric(BorderWidth), active, (p == WindowArea::ExpandButton));
	}
	if(drawAll || (p != pressed && (p == WindowArea::HideButton || pressed == WindowArea::HideButton))){
		DrawMinButton(w - (GetMetric(ButtonSize) * 2) - GetMetric(BorderWidth), GetMetric(BorderWidth), active, (p == WindowArea::HideButton));
	}
	if(drawAll || (p != pressed && (p == WindowArea::CloseButton || pressed == WindowArea::CloseButton))){
		DrawCloseButton(w - (GetMetric(ButtonSize) * 3) - GetMetric(BorderWidth), GetMetric(BorderWidth), active, (p == WindowArea::CloseButton));
	}
	width = w;
	title = t;
	pressed = p;
	if(active) gds_active_title = ret;
	else gds_inactive_title = ret;
	return ret;
}

TitleBar::~TitleBar(){
	if(gds_active_title){
		GDS_SelectSurface(gds_active_title);
		GDS_DeleteSurface();
	}
	if(gds_inactive_title){
		GDS_SelectSurface(gds_inactive_title);
		GDS_DeleteSurface();
	}
}

static pair<bool, gds_DrawingOp> DrawBorderHorzLine(int32_t x1, int32_t y, int32_t x2, const Rect &bounds){
	if((x1 < bounds.x && x2 < bounds.x) || (x1 >= bounds.x + (int32_t)bounds.w && x2 >= bounds.x + (int32_t)bounds.w) || y < bounds.y || y > bounds.y + (int32_t)bounds.h) return {false, gds_DrawingOp()};
	if(x1 > x2) swap(x1, x2);
	if(x1 < bounds.x) x1 = bounds.x;
	if(x2 > bounds.x + (int32_t)bounds.w) x2 = bounds.x + bounds.w;
	return {true, GDS_Line_Op(x1, y, x2, y, borderColour, 1)};
}

static pair<bool, gds_DrawingOp> DrawBorderVertLine(int32_t x, int32_t y1, int32_t y2, const Rect &bounds){
	if((y1 < bounds.y && y2 < (int32_t)bounds.y) || (y1 >= bounds.y + (int32_t)bounds.h && y2 >= bounds.y + (int32_t)bounds.h) || x < bounds.x || x > bounds.x + (int32_t)bounds.w) return {false, gds_DrawingOp()};
	if(y1 > y2) swap(y1, y2);
	if(y1 < bounds.y) y1 = bounds.y;
	if(y2 > bounds.y + (int32_t)bounds.h) y2 = bounds.y + bounds.h;
	return {true, GDS_Line_Op(x, y1, x, y2, borderColour, 1)};
}

void DrawBorder(uint32_t x, uint32_t y, uint32_t w, uint32_t h, const Rect &bounds){
	borderColour = GetColour(BorderColour);
	vector<gds_DrawingOp> ops;
	auto l1 = DrawBorderHorzLine(x, y, x + w - 1, bounds);
	if(l1.first) ops.push_back(l1.second);
	auto l2 = DrawBorderHorzLine(x, y + h - 1, x + w - 1, bounds);
	if(l2.first) ops.push_back(l2.second);
	auto l3 = DrawBorderVertLine(x, y, y + h - 1, bounds);
	if(l3.first) ops.push_back(l3.second);
	auto l4 = DrawBorderVertLine(x + w - 1, y, y + h - 1, bounds);
	if(l4.first) ops.push_back(l4.second);
	GDS_MultiDrawingOps(ops.size(), &ops[0], NULL);
}

uint64_t DrawMenuItem(const string &text, uint32_t flags, uint64_t image, uint32_t width, bool selected){
	DBG("WM DrawMenuItem: \"" << text << "\", " << flags << ", " << image << ", " << width << ", " << selected); 
	uint64_t ret = 0;
	if(!(flags & wm_MenuItemFlags::Seperator)){
		ret = GDS_NewSurface(gds_SurfaceType::Bitmap, width, GetMetric(MenuItemHeight));
		if(selected) GDS_Box(0, 0, width, GetMetric(MenuItemHeight), GetColour(MenuSelectionColour), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		else GDS_Box(0, 0, width, GetMetric(MenuItemHeight), GetColour(MenuBackgroundColour), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		uint32_t lpos = GetMetric(MenuItemMargin);
		if(image){
			GDS_SelectSurface(image);
			gds_SurfaceInfo image_info = GDS_SurfaceInfo();
			GDS_SelectSurface(ret);
			GDS_Blit(image, 0, 0, image_info.w, image_info.h, lpos, GetMetric(MenuItemMargin), image_info.w, image_info.h);
			lpos += image_info.w;
			lpos += GetMetric(MenuItemMargin);
		}
		if(!(flags & wm_MenuItemFlags::ImageOnly)){
			GDS_Text(lpos, GetMetric(MenuItemHeight) - GetMetric(MenuItemMargin), text.c_str(), menuFont, GetMetric(MenuFontSize), GetColour(MenuForegroundColour));
		}
		if((flags & wm_MenuItemFlags::ChildMenu)){
			gds_Point points[] = { 
				{ (int32_t)width - GetMetric(MenuItemHeight) + GetMetric(MenuItemMargin), (GetMetric(MenuItemMargin) * 2) },
				{ (int32_t)width - GetMetric(MenuItemHeight) + GetMetric(MenuItemMargin), GetMetric(MenuItemHeight) - (GetMetric(MenuItemMargin) * 2) },
				{ (int32_t)width - (GetMetric(MenuItemMargin) * 2), GetMetric(MenuItemHeight) / 2}
			};
			uint32_t col = GetColour(MenuForegroundColour);
			GDS_Polygon(3, points, true, col, col, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		}
	}else{
		uint32_t height = (GetMetric(MenuItemMargin) * 2) + 1;
		ret = GDS_NewSurface(gds_SurfaceType::Bitmap, width, height);
		GDS_Box(0, 0, width, GetMetric(MenuItemHeight), GetColour(MenuBackgroundColour), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		GDS_Line(GetMetric(MenuItemMargin), height / 2, width - GetMetric(MenuItemMargin), height / 2, GetColour(MenuForegroundColour), 1);
	}
	return ret;
}
