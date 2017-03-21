#include <gds/libgds.h>
#include "libgds_internal.hpp"
#include <cstring>

#pragma GCC diagnostic ignored "-Wunused-parameter"

extern "C" gds_DrawingOp GDS_Dot_Op(int32_t x, int32_t y, uint32_t colour, uint8_t size){
	gds_DrawingOp op;
	op.type = gds_DrawingOpType::Dot;
	op.Dot.x = x; op.Dot.y = y;
	op.Common.lineColour = colour;
	op.Common.lineWidth = size;
	return op;
}

extern "C" uint32_t GDS_Dot(int32_t x, int32_t y, uint32_t colour, uint8_t size){
	return GDS_AddDrawingOp(GDS_Dot_Op(x, y, colour, size));
}

extern "C" gds_DrawingOp GDS_Line_Op(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t colour, uint8_t width, uint32_t style){
	gds_DrawingOp op;
	op.type = gds_DrawingOpType::Line;
	op.Line.x1 = x1; op.Line.y1 = y1;
	op.Line.x2 = x2; op.Line.y2 = y2;
	op.Common.lineColour = colour;
	op.Common.lineWidth = width;
	op.Common.lineStyle = style;
	return op;
}

extern "C" uint32_t GDS_Line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t colour, uint8_t width, uint32_t style){
	return GDS_AddDrawingOp(GDS_Line_Op(x1, y1, x2, y2, colour, width, style));
}

extern "C" gds_DrawingOp GDS_Box_Op(int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t lineColour, uint32_t fillColour, uint8_t lineWidth, uint32_t lineStyle, uint32_t fillStyle){
	gds_DrawingOp op;
	op.type = gds_DrawingOpType::Box;
	op.Box.x = x; op.Box.y = y;
	op.Box.w = w; op.Box.h = h;
	op.Common.lineColour = lineColour;
	op.Common.fillColour = fillColour;
	op.Common.lineWidth = lineWidth;
	op.Common.lineStyle = lineStyle;
	op.Common.fillStyle = fillStyle;
	return op;
}

extern "C" uint32_t GDS_Box(int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t lineColour, uint32_t fillColour, uint8_t lineWidth, uint32_t lineStyle, uint32_t fillStyle){
	return GDS_AddDrawingOp(GDS_Box_Op(x, y, w, h, lineColour, fillColour, lineWidth, lineStyle, fillStyle));
}

extern "C" gds_DrawingOp GDS_Ellipse_Op(int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t lineColour, uint32_t fillColour, uint8_t lineWidth, uint32_t lineStyle, uint32_t fillStyle){
	gds_DrawingOp op;
	op.type = gds_DrawingOpType::Ellipse;
	op.Ellipse.x = x; op.Ellipse.y = y;
	op.Ellipse.w = w; op.Ellipse.h = h;
	op.Common.lineColour = lineColour;
	op.Common.fillColour = fillColour;
	op.Common.lineWidth = lineWidth;
	op.Common.lineStyle = lineStyle;
	op.Common.fillStyle = fillStyle;
	return op;
}

extern "C" uint32_t GDS_Ellipse(int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t lineColour, uint32_t fillColour, uint8_t lineWidth, uint32_t lineStyle, uint32_t fillStyle){
	return GDS_AddDrawingOp(GDS_Ellipse_Op(x, y, w, h, lineColour, fillColour, lineWidth, lineStyle, fillStyle));
}

extern "C" gds_DrawingOp GDS_Arc_Op(int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t a1, uint32_t a2, uint32_t lineColour, uint32_t fillColour, uint8_t lineWidth, uint32_t lineStyle, uint32_t fillStyle){
	gds_DrawingOp op;
	op.type = gds_DrawingOpType::Arc;
	op.Arc.x = x; op.Arc.y = y;
	op.Arc.w = w; op.Arc.h = h;
	op.Arc.a1 = a1; op.Arc.a2 = a2;
	op.Common.lineColour = lineColour;
	op.Common.fillColour = fillColour;
	op.Common.lineWidth = lineWidth;
	op.Common.lineStyle = lineStyle;
	op.Common.fillStyle = fillStyle;
	return op;
}

extern "C" uint32_t GDS_Arc(int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t a1, uint32_t a2, uint32_t lineColour, uint32_t fillColour, uint8_t lineWidth, uint32_t lineStyle, uint32_t fillStyle){
	return GDS_AddDrawingOp(GDS_Arc_Op(x, y, w, h, a1, a2, lineColour, fillColour, lineWidth, lineStyle, fillStyle));
}

extern "C" gds_DrawingOp GDS_Polygon_Op(bool closed, uint32_t lineColour, uint32_t fillColour, uint8_t lineWidth, uint32_t lineStyle, uint32_t fillStyle){
	gds_DrawingOp op;
	op.type = gds_DrawingOpType::Polygon;
	op.Polygon.closed = closed;
	op.Common.lineColour = lineColour;
	op.Common.fillColour = fillColour;
	op.Common.lineWidth = lineWidth;
	op.Common.lineStyle = lineStyle;
	op.Common.fillStyle = fillStyle;
	return op;
}

extern "C" gds_OpParameters *GDS_Polygon_Params(uint32_t op_id, size_t points, gds_Point *pointData){
	gds_OpParameters *params = (gds_OpParameters*)new char[sizeof(gds_OpParameters) + (sizeof(gds_Point) * points)];
	params->type = gds_DrawingOpType::Polygon;
	params->op_id = op_id;
	params->size = (sizeof(gds_Point) * points);
	memcpy(params->data, pointData, (sizeof(gds_Point) * points));
	return params;
}

extern "C" uint32_t GDS_Polygon(size_t points, gds_Point *pointData, bool closed, uint32_t lineColour, uint32_t fillColour, uint8_t lineWidth, uint32_t lineStyle, uint32_t fillStyle){
	uint32_t id = GDS_AddDrawingOp(GDS_Polygon_Op(closed, lineColour, fillColour, lineWidth, lineStyle, fillStyle));
	gds_OpParameters *params = GDS_Polygon_Params(id, points, pointData);
	GDS_SetOpParameters(params);
	delete params;
	return id;
}

extern "C" gds_DrawingOp GDS_Text_Op(int32_t x, int32_t y, uint32_t fontID, uint32_t size, uint32_t colour, uint8_t style){
	gds_DrawingOp op;
	op.type = gds_DrawingOpType::Text;
	op.Text.x = x;
	op.Text.y = y;
	op.Text.fontID = fontID;
	op.Text.size = size;
	op.Common.lineColour = colour;
	op.Common.lineStyle = style;
	return op;
}

extern "C" gds_OpParameters *GDS_Text_Params(uint32_t op_id, const char *text){
	gds_OpParameters *params = (gds_OpParameters*)new char[sizeof(gds_OpParameters) + strlen(text) + 1]();
	params->type = gds_DrawingOpType::Text;
	params->op_id = op_id;
	params->size = strlen(text);
	strcpy(params->data, text);
	return params;
}

extern "C" uint32_t GDS_Text(int32_t x, int32_t y, const char *text, uint32_t fontID, uint32_t size, uint32_t colour, uint8_t style){
	uint32_t id = GDS_AddDrawingOp(GDS_Text_Op(x, y, fontID, size, colour, style));
	gds_OpParameters *params = GDS_Text_Params(id, text);
	GDS_SetOpParameters(params);
	delete params;
	return id;
}

extern "C" gds_DrawingOp GDS_TextChar_Op(int32_t x, int32_t y, char c, uint32_t fontID, uint32_t size, uint32_t colour, uint8_t style){
	gds_DrawingOp op;
	op.type = gds_DrawingOpType::TextChar;
	op.TextChar.x = x;
	op.TextChar.y = y;
	op.TextChar.fontID = fontID;
	op.TextChar.size = size;
	op.TextChar.c = c;
	op.Common.lineColour = colour;
	op.Common.lineStyle = style;
	return op;
}

extern "C" uint32_t GDS_TextChar(int32_t x, int32_t y, char c, uint32_t fontID, uint32_t size, uint32_t colour, uint8_t style){
	return GDS_AddDrawingOp(GDS_TextChar_Op(x, y, c, fontID, size, colour, style));
}

extern "C" gds_DrawingOp GDS_Blit_Op(uint64_t src, uint32_t srcX, uint32_t srcY, uint32_t srcW, uint32_t srcH, int32_t dstX, int32_t dstY, uint32_t dstW, uint32_t dstH, uint32_t scale, uint32_t flags){
	gds_DrawingOp op;
	op.type = gds_DrawingOpType::Blit;
	op.Blit.src = src;
	op.Blit.srcX = srcX;
	op.Blit.srcY = srcY;
	op.Blit.srcW = srcW;
	op.Blit.srcH = srcH;
	op.Blit.dstX = dstX;
	op.Blit.dstY = dstY;
	op.Blit.dstW = dstW;
	op.Blit.dstH = dstH;
	op.Blit.scale = scale;
	op.Blit.flags = flags;
	return op;
}

extern "C" uint32_t GDS_Blit(uint64_t src, uint32_t srcX, uint32_t srcY, uint32_t srcW, uint32_t srcH, int32_t dstX, int32_t dstY, uint32_t dstW, uint32_t dstH, uint32_t scale, uint32_t flags){
	return GDS_AddDrawingOp(GDS_Blit_Op(src, srcX, srcY, srcW, srcH, dstX, dstY, dstW, dstH, scale, flags));
}

