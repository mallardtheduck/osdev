#include <gds/libgds.h>
#include "drawing.hpp"
#include "metrics.hpp"
#include <utility>
#include <wm/wm.h>
#include <sstream>
#include <btos.h>
#include <gds/surface.hpp>

#define DBG(x) do{std::stringstream dbgss; dbgss << x << std::endl; bt_zero(dbgss.str().c_str());}while(0)

using namespace std;
using namespace gds;

static Font titleActiveFont;
static Font titleInactiveFont;
static Font menuButtonFont;
static Font menuFont;

void InitDrawing(){
	titleActiveFont = Font::Get(GetSetting(TitleFontName), gds_FontStyle::Bold);
	titleInactiveFont = Font::Get(GetSetting(TitleFontName), gds_FontStyle::Normal);
	menuButtonFont = Font::Get(GetSetting(MenuButtonFontName), gds_FontStyle::Bold);
	menuFont = Font::Get(GetSetting(MenuFontName), gds_FontStyle::Bold);
}

static Colour buttonHighlightColour, buttonFaceColour, buttonShadowColour, borderColour, lineColour, titleBarColour, inactiveTitleColour;
static Colour separatorColour, titleTextColour, symbolColour, disabledSymbolColour;

static void DrawButtonUp(Surface &surf, const Rect &r, bool active){
	vector<gds_DrawingOp> ops;
	ops.push_back(GDS_Box_Op(r.x+1, r.y+1, r.w-1, r.h-1, buttonHighlightColour.id, buttonFaceColour.id, 1, gds_LineStyle::Solid, gds_FillStyle::Filled));
	ops.push_back(GDS_Line_Op(r.x+1, r.y+r.h-2, r.x+r.w-2, r.y+r.h-2, buttonShadowColour.id, 1));
	ops.push_back(GDS_Line_Op(r.x+r.w-2, r.y+r.h-1, r.x+r.w-2, r.y+2, buttonShadowColour.id, 1));
	ops.push_back(GDS_Box_Op(r.x, r.y, r.w, r.h, lineColour.id, borderColour.id, 1));
	ops.push_back(GDS_Dot_Op(r.x, r.y, active?titleBarColour.id:inactiveTitleColour.id, 1));
	ops.push_back(GDS_Dot_Op(r.x+r.w-1, r.y, active?titleBarColour.id:inactiveTitleColour.id, 1));
	ops.push_back(GDS_Dot_Op(r.x, r.y+r.h-1, active?titleBarColour.id:inactiveTitleColour.id, 1));
	ops.push_back(GDS_Dot_Op(r.x+r.w-1, r.y+r.h-1, active?titleBarColour.id:inactiveTitleColour.id, 1));
	surf.AddDrawingOps(ops);
}

static void DrawButtonDown(Surface &surf, const Rect &r, bool active){
	vector<gds_DrawingOp> ops;
	ops.push_back(GDS_Box_Op(r.x+1, r.y+1, r.w-1, r.h-1, buttonShadowColour.id, buttonFaceColour.id, 1, gds_LineStyle::Solid, gds_FillStyle::Filled));
	ops.push_back(GDS_Line_Op(r.x+1, r.y+r.h-2, r.x+r.w-2, r.y+r.h-2, buttonHighlightColour.id, 1));
	ops.push_back(GDS_Line_Op(r.x+r.w-2, r.y+r.h-1, r.x+r.w-2, r.y+2, buttonHighlightColour.id, 1));
	ops.push_back(GDS_Box_Op(r.x, r.y, r.w, r.h, lineColour.id, borderColour.id, 1));
	ops.push_back(GDS_Dot_Op(r.x, r.y, active?titleBarColour.id:inactiveTitleColour.id, 1));
	ops.push_back(GDS_Dot_Op(r.x+r.w-1, r.y, active?titleBarColour.id:inactiveTitleColour.id, 1));
	ops.push_back(GDS_Dot_Op(r.x, r.y+r.h-1, active?titleBarColour.id:inactiveTitleColour.id, 1));
	ops.push_back(GDS_Dot_Op(r.x+r.w-1, r.y+r.h-1, active?titleBarColour.id:inactiveTitleColour.id, 1));
	surf.AddDrawingOps(ops);
}

static void DrawMaxButton(Surface &surf, const Point &p, bool active, bool down = false, bool enabled = true){
	uint32_t buttonSize = GetMetric(TitleBarSize)-2;
	if(down) DrawButtonDown(surf, {p, buttonSize, buttonSize}, active);
	else DrawButtonUp(surf, {p, buttonSize, buttonSize}, active);
	uint32_t borderWidth = buttonSize / 4;
	Colour fgCol = enabled ? symbolColour : disabledSymbolColour;
	surf.Box({(int32_t)(p.x + borderWidth), (int32_t)(p.y + borderWidth), buttonSize - (2*borderWidth), buttonSize - (2*borderWidth)}, fgCol, Colour(), 2);
}

static void DrawMinButton(Surface &surf, const Point &p, bool active, bool down = false, bool enabled = true){
	uint32_t buttonSize = GetMetric(ButtonSize);
	if(down) DrawButtonDown(surf, {p, buttonSize, buttonSize}, active);
	else DrawButtonUp(surf, {p, buttonSize, buttonSize}, active);
	uint32_t symbolSize = buttonSize / 4;
	uint32_t borderWidth = (buttonSize - symbolSize) / 2;
	Colour fgCol = enabled ? symbolColour : disabledSymbolColour;
	surf.Box({(int32_t)(p.x + borderWidth), (int32_t)(p.y + borderWidth), buttonSize - (2*borderWidth), buttonSize - (2*borderWidth)}, Colour(), fgCol, 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
}

static void DrawCloseButton(Surface &surf, const Point &p, bool active, bool down = false, bool enabled = true){
	uint32_t buttonSize = GetMetric(ButtonSize);
	if(down) DrawButtonDown(surf, {p, buttonSize, buttonSize}, active);
	else DrawButtonUp(surf, {p, buttonSize, buttonSize}, active);
	uint32_t half = buttonSize / 2;
	uint32_t quarter = buttonSize / 4;
	Colour fgCol = enabled ? symbolColour : disabledSymbolColour;
	vector<gds_DrawingOp> ops;
	ops.push_back(GDS_Line_Op(p.x + quarter, p.y + quarter, p.x + half, p.y + half, fgCol.id, 2));
	ops.push_back(GDS_Line_Op(p.x + (buttonSize - quarter) - 1, p.y + quarter, p.x + half - 1, p.y + half, fgCol.id, 2));
	ops.push_back(GDS_Line_Op(p.x + quarter, p.y + (buttonSize - quarter) - 1, p.x + half, p.y + half - 1, fgCol.id, 2));
	ops.push_back(GDS_Line_Op(p.x + (buttonSize - quarter) - 1, p.y + (buttonSize - quarter) - 1, p.x + half - 1, p.y + half - 1, fgCol.id, 2));
	surf.AddDrawingOps(ops);
}

static void DrawMenuButton(Surface &surf, const Point &p, bool active, bool down = false, bool enabled = true){
	uint32_t buttonHeight = GetMetric(ButtonSize);
	uint32_t buttonWidth = GetMetric(MenuButtonWidth);
	if(down) DrawButtonDown(surf, {p, buttonWidth, buttonHeight}, active);
	else DrawButtonUp(surf, {p, buttonWidth, buttonHeight}, active);
	uint32_t borderWidth = buttonHeight / 4;
	uint32_t symLength = buttonHeight - borderWidth;
	Colour fgCol = enabled ? symbolColour : disabledSymbolColour;
	vector<gds_DrawingOp> ops;
	ops.push_back(GDS_Line_Op(p.x + borderWidth, p.y + borderWidth, p.x + symLength, p.y + borderWidth, fgCol.id, 2));
	ops.push_back(GDS_Line_Op(p.x + borderWidth, p.y + (buttonHeight / 2), p.x + symLength, p.y + (buttonHeight / 2), fgCol.id, 2));
	ops.push_back(GDS_Line_Op(p.x + borderWidth, p.y + buttonHeight - borderWidth, p.x + symLength, p.y + buttonHeight - borderWidth, fgCol.id, 2));
	surf.AddDrawingOps(ops);
	surf.Text({(int32_t)(p.x + symLength + 5), (int32_t)(p.y + buttonHeight - 5)}, "Menu", menuButtonFont, GetMetric(MenuButtonFontSize), fgCol);
}

shared_ptr<Surface> TitleBar::Draw(uint32_t w, const string &t, bool active, uint32_t options, WindowArea p){
	shared_ptr<Surface> ret;
	bool drawAll = false;
	if(w != width){
		if(gds_active_title){
			gds_active_title.reset();
		}
		if(gds_inactive_title){
			gds_inactive_title.reset();
		}
	}
	if((active && !gds_active_title) || (!active && !gds_inactive_title)){
		ret = make_shared<Surface>(gds_SurfaceType::Bitmap, w, GetMetric(TitleBarSize));
		drawAll = true;
	}else{
		if(active) ret = gds_active_title;
		else ret = gds_inactive_title;
	}
	if(t != title) drawAll = true;
	if(options != window_options) drawAll = true;
	
	ret->BeginQueue();
	if(drawAll || p != pressed){
		buttonHighlightColour = GetColour(*ret, ButtonHighlightColour);
		buttonFaceColour = GetColour(*ret, ButtonFaceColour);
		buttonShadowColour = GetColour(*ret, ButtonShadowColour);
		borderColour = GetColour(*ret, BorderColour); 
		lineColour = GetColour(*ret, LineColour); 
		titleBarColour = GetColour(*ret, TitleBarColour);
		inactiveTitleColour = GetColour(*ret, InactiveTitleColour);
		separatorColour = GetColour(*ret, SeparatorColour);
		titleTextColour = GetColour(*ret, TitleTextColour);
		symbolColour = GetColour(*ret, SymbolColour);
		disabledSymbolColour = GetColour(*ret, DisabledSymbolColour);
	}
	
	if(drawAll) ret->Box({0, 0, w, (uint32_t)GetMetric(TitleBarSize)}, separatorColour, active?titleBarColour:inactiveTitleColour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	if(drawAll || (p != pressed && (p == WindowArea::MenuButton || pressed == WindowArea::MenuButton))){
		bool enabled = !(options & wm_WindowOptions::NoMenu);
		DrawMenuButton(*ret, {GetMetric(BorderWidth), GetMetric(BorderWidth)}, active, (enabled && p == WindowArea::MenuButton), enabled);
	}
	if(drawAll){
		Font font = active ? titleActiveFont : titleInactiveFont;
		ret->Text({GetMetric(MenuButtonWidth) + GetMetric(TitleTextMargin), GetMetric(TitleBarSize) - GetMetric(TitleTextBaseline)}, t, font, GetMetric(TitleFontSize), titleTextColour, 0);
	}
	if(drawAll || (p != pressed && (p == WindowArea::ExpandButton || pressed == WindowArea::ExpandButton))){
		bool enabled = !(options & wm_WindowOptions::NoExpand);
		DrawMaxButton(*ret, {(int32_t)(w - GetMetric(ButtonSize) - GetMetric(BorderWidth)), GetMetric(BorderWidth)}, active, (enabled && p == WindowArea::ExpandButton), enabled);
	}
	if(drawAll || (p != pressed && (p == WindowArea::HideButton || pressed == WindowArea::HideButton))){
		bool enabled = !(options & wm_WindowOptions::NoHide);
		DrawMinButton(*ret, {(int32_t)(w - (GetMetric(ButtonSize) * 2) - GetMetric(BorderWidth)), GetMetric(BorderWidth)}, active, (enabled && p == WindowArea::HideButton), enabled);
	}
	if(drawAll || (p != pressed && (p == WindowArea::CloseButton || pressed == WindowArea::CloseButton))){
		bool enabled = !(options & wm_WindowOptions::NoClose);
		DrawCloseButton(*ret, {(int32_t)(w - (GetMetric(ButtonSize) * 3) - GetMetric(BorderWidth)), GetMetric(BorderWidth)}, active, (enabled && p == WindowArea::CloseButton), enabled);
	}
	width = w;
	title = t;
	pressed = p;
	window_options = options;
	if(active) gds_active_title = ret;
	else gds_inactive_title = ret;
	ret->CommitQueue();
	return ret;
}

TitleBar::~TitleBar(){
}

static pair<bool, gds_DrawingOp> DrawBorderHorzLine(int32_t x1, int32_t y, int32_t x2, const Rect &bounds){
	if((x1 < bounds.x && x2 < bounds.x) || (x1 >= bounds.x + (int32_t)bounds.w && x2 >= bounds.x + (int32_t)bounds.w) || y < bounds.y || y > bounds.y + (int32_t)bounds.h) return {false, gds_DrawingOp()};
	if(x1 > x2) swap(x1, x2);
	if(x1 < bounds.x) x1 = bounds.x;
	if(x2 > bounds.x + (int32_t)bounds.w) x2 = bounds.x + bounds.w;
	return {true, GDS_Line_Op(x1, y, x2, y, borderColour.id, 1)};
}

static pair<bool, gds_DrawingOp> DrawBorderVertLine(int32_t x, int32_t y1, int32_t y2, const Rect &bounds){
	if((y1 < bounds.y && y2 < (int32_t)bounds.y) || (y1 >= bounds.y + (int32_t)bounds.h && y2 >= bounds.y + (int32_t)bounds.h) || x < bounds.x || x > bounds.x + (int32_t)bounds.w) return {false, gds_DrawingOp()};
	if(y1 > y2) swap(y1, y2);
	if(y1 < bounds.y) y1 = bounds.y;
	if(y2 > bounds.y + (int32_t)bounds.h) y2 = bounds.y + bounds.h;
	return {true, GDS_Line_Op(x, y1, x, y2, borderColour.id, 1)};
}

void DrawBorder(Surface &surf, const Rect &r, const Rect &bounds){
	borderColour = GetColour(surf, BorderColour);
	vector<gds_DrawingOp> ops;
	auto l1 = DrawBorderHorzLine(r.x, r.y, r.x + r.w - 1, bounds);
	if(l1.first) ops.push_back(l1.second);
	auto l2 = DrawBorderHorzLine(r.x, r.y + r.h - 1, r.x + r.w - 1, bounds);
	if(l2.first) ops.push_back(l2.second);
	auto l3 = DrawBorderVertLine(r.x, r.y, r.y + r.h - 1, bounds);
	if(l3.first) ops.push_back(l3.second);
	auto l4 = DrawBorderVertLine(r.x + r.w - 1, r.y, r.y + r.h - 1, bounds);
	if(l4.first) ops.push_back(l4.second);
	surf.AddDrawingOps(ops);
}

Surface DrawMenuItem(const string &text, uint32_t flags, const Surface *image, uint32_t width, bool selected){ 
	if(!(flags & wm_MenuItemFlags::Separator)){
		Surface ret(gds_SurfaceType::Bitmap, width, GetMetric(MenuItemHeight));
		ret.BeginQueue();
		if(selected) ret.Box({0, 0, width, (uint32_t)GetMetric(MenuItemHeight)}, Colour(), GetColour(ret, MenuSelectionColour), 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
		else ret.Box({0, 0, width, (uint32_t)GetMetric(MenuItemHeight)}, Colour(), GetColour(ret, MenuBackgroundColour), 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
		int32_t lpos = GetMetric(MenuItemMargin);
		if(image){
			gds_SurfaceInfo image_info = image->Info();
			int32_t imageXPos = (GetMetric(MenuItemHeight) - image_info.h) / 2;
			ret.Blit(*image, {0, 0, image_info.w, image_info.h}, {lpos, imageXPos, image_info.w, image_info.h});
			lpos += image_info.w;
			lpos += GetMetric(MenuItemMargin);
		}
		if(!(flags & wm_MenuItemFlags::ImageOnly)){
			Colour fgCol = (flags & wm_MenuItemFlags::Disabled) ? GetColour(ret, MenuForegroundDisabledColour) : GetColour(ret, MenuForegroundColour);
			ret.Text({lpos, GetMetric(MenuItemHeight) - GetMetric(MenuItemMargin)}, text, menuFont, GetMetric(MenuFontSize), fgCol);
		}
		if((flags & wm_MenuItemFlags::ChildMenu)){
			vector<Point> points = { 
				{ (int32_t)width - GetMetric(MenuItemHeight) + GetMetric(MenuItemMargin), (GetMetric(MenuItemMargin) * 2) },
				{ (int32_t)width - GetMetric(MenuItemHeight) + GetMetric(MenuItemMargin), GetMetric(MenuItemHeight) - (GetMetric(MenuItemMargin) * 2) },
				{ (int32_t)width - (GetMetric(MenuItemMargin) * 2), GetMetric(MenuItemHeight) / 2}
			};
			Colour col = GetColour(ret, MenuForegroundColour);
			ret.Polygon(points, true, col, col, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		}
		ret.CommitQueue();
		return ret;
	}else{
		int32_t height = (GetMetric(MenuItemMargin) * 2) + 1;
		Surface ret(gds_SurfaceType::Bitmap, width, height);
		ret.BeginQueue();
		ret.Box({0, 0, width, (uint32_t)GetMetric(MenuItemHeight)}, Colour(), GetColour(ret, MenuBackgroundColour), 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
		ret.Line({GetMetric(MenuItemMargin), height / 2}, {(int32_t)(width - GetMetric(MenuItemMargin)), height / 2}, GetColour(ret, MenuForegroundColour));
		ret.CommitQueue();		
		return ret;
	}
}
