#include <gds/libgds.h>
#include "metrics.hpp"

void DrawButton(uint32_t x, uint32_t y, uint32_t w, uint32_t h){
	GDS_Box(x+1, y+1, w-2, h-2, GetColour(ButtonHighlightColour), GetColour(ButtonFaceColour), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	GDS_Line(x+1, y+h-1, x+w-1, y+h-1, GetColour(ButtonShadowColour), 1);
	GDS_Line(x+w-1, y+h-1, x+w-1, y+1, GetColour(ButtonShadowColour), 1);
	GDS_Box(x, y, w, h, GetColour(LineColour), GetColour(BorderColour), 1);
	GDS_Dot(x, y, GetColour(TitleBarColour), 1);
	GDS_Dot(x+w, y, GetColour(TitleBarColour), 1);
	GDS_Dot(x, y+h, GetColour(TitleBarColour), 1);
	GDS_Dot(x+w, y+h, GetColour(TitleBarColour), 1);
}

void DrawTitleBar(uint32_t x, uint32_t y, uint32_t w){
	GDS_Box(x, y, w, GetMetric(TitleBarSize), GetColour(SeperatorColour), GetColour(TitleBarColour), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	uint32_t buttonSize = GetMetric(TitleBarSize)-2;
	DrawButton(x+1, y+1, buttonSize, buttonSize);
	DrawButton(x + w - buttonSize - 1, y+1, buttonSize, buttonSize);
	DrawButton(x + w - (buttonSize * 2) - 1, y+1, buttonSize, buttonSize);
	DrawButton(x + w - (buttonSize * 3) - 1, y+1, buttonSize, buttonSize);
}

void DrawBorder(uint32_t x, uint32_t y, uint32_t w, uint32_t h){
	GDS_Box(x, y, w, h, GetColour(BorderColour), 1);
}