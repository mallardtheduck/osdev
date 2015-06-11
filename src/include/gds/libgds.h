#ifndef _LIBGDS_H
#define _LIBGDS_H

#include "gds.h"
#include "../video_dev.h"

#ifdef __cplusplus
#define GDS_DEFAULT(x) = x
#else
#define GDS_DEFAULT(x)
#endif

#ifdef __cplusplus
extern "C" {
#endif

gds_Info GDS_Info();
uint64_t GDS_NewSurface(ENUM_NAME(gds_SurfaceType) type, uint32_t w, uint32_t h, uint32_t scale, ENUM_NAME(gds_ColourType) colourType);
void GDS_DeleteSurface();
uint64_t GDS_SelectSurface(uint64_t id);
size_t GDS_AddDrawingOp(gds_DrawingOp op);
void GDS_RemoveDrawingOp(size_t index);
gds_DrawingOp GDS_GetDrawingOp(size_t index);
gds_SurfaceInfo GDS_SurfaceInfo();
void GDS_SetScale(uint32_t scale);
uint32_t GDS_GetColour(uint32_t r, uint32_t g, uint32_t b);
void GDS_SelectScreen();
void GDS_UpdateScreen(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
void GDS_SetScreenMode(bt_vidmode mode);

gds_DrawingOp GDS_Dot(uint32_t x, uint32_t y, gds_Colour colour, uint8_t size GDS_DEFAULT(1));
gds_DrawingOp GDS_Line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, gds_Colour colour, uint8_t width GDS_DEFAULT(1), uint32_t style GDS_DEFAULT(ENUM_GET(gds_LineStyle, Default)));
gds_DrawingOp GDS_Box(uint32_t x, uint32_t y, uint32_t w, uint32_t h, gds_Colour lineColour, gds_Colour fillColour, uint32_t lineWidth GDS_DEFAULT(1), uint32_t lineStyle GDS_DEFAULT(ENUM_GET(gds_LineStyle, Default)), uint32_t fillStyle GDS_DEFAULT(ENUM_GET(gds_FillStyle, Default)));
gds_DrawingOp GDS_Ellipse(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t a1, uint32_t a2, gds_Colour lineColour, gds_Colour fillColour, uint32_t lineWidth GDS_DEFAULT(1), uint32_t lineStyle GDS_DEFAULT(ENUM_GET(gds_LineStyle, Default)), uint32_t fillStyle GDS_DEFAULT(ENUM_GET(gds_FillStyle, Default)));
gds_DrawingOp GDS_Arc(size_t points, gds_Point *pointData,  bool closed, gds_Colour lineColour, gds_Colour fillColour, uint32_t lineWidth GDS_DEFAULT(1), uint32_t lineStyle GDS_DEFAULT(ENUM_GET(gds_LineStyle, Default)), uint32_t fillStyle GDS_DEFAULT(ENUM_GET(gds_FillStyle, Default)));
gds_DrawingOp GDS_Polygon(size_t points, gds_Point *pointData, bool closed,  gds_Colour lineColour, gds_Colour fillColour, uint32_t lineWidth GDS_DEFAULT(1), uint32_t lineStyle GDS_DEFAULT(ENUM_GET(gds_LineStyle, Default)), uint32_t fillStyle GDS_DEFAULT(ENUM_GET(gds_FillStyle, Default)));
gds_DrawingOp GDS_Text(char *string, uint32_t fontID, uint32_t size, gds_Colour colour, uint8_t style GDS_DEFAULT(ENUM_GET(gds_TextStyle, Normal)));

#ifdef __cplusplus
}
#endif

#endif