#ifndef _LIBGDS_H
#define _LIBGDS_H

#include "gds.h"
#include <dev/video_dev.h>

#ifdef __cplusplus
#define GDS_DEFAULT(x) = x
#else
#define GDS_DEFAULT(x)
#endif

#ifdef __cplusplus
extern "C" {
#endif

gds_Info GDS_Info();
uint64_t GDS_NewSurface(ENUM_NAME(gds_SurfaceType) type, uint32_t w, uint32_t h, uint32_t scale GDS_DEFAULT(100), ENUM_NAME(gds_ColourType) colourType GDS_DEFAULT(ENUM_GET(gds_ColourType, Indexed)));
void GDS_DeleteSurface();
uint64_t GDS_SelectSurface(uint64_t id);
size_t GDS_AddDrawingOp(gds_DrawingOp op);
void GDS_RemoveDrawingOp(size_t index);
gds_DrawingOp GDS_GetDrawingOp(size_t index);
gds_SurfaceInfo GDS_SurfaceInfo();
void GDS_SetScale(uint32_t scale);
uint32_t GDS_GetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a GDS_DEFAULT(0));
void GDS_SetOpParameters(const gds_OpParameters *params);
void GDS_SelectScreen();
void GDS_UpdateScreen(uint32_t x GDS_DEFAULT(0), uint32_t y GDS_DEFAULT(0), uint32_t w GDS_DEFAULT(0), uint32_t h GDS_DEFAULT(0));
void GDS_SetScreenMode(bt_vidmode mode);
void GDS_SetCursor(uint64_t surfaceID, uint32_t hotx, uint32_t hoty);
void GDS_CursorVisibility(bool visible);

void GDS_Dot(int32_t x, int32_t y, uint32_t colour, uint8_t size GDS_DEFAULT(1));
void GDS_Line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t colour, uint8_t width GDS_DEFAULT(1), uint32_t style GDS_DEFAULT(ENUM_GET(gds_LineStyle, Solid)));
void GDS_Box(int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t lineColour, uint32_t fillColour, uint8_t lineWidth GDS_DEFAULT(1), uint32_t lineStyle GDS_DEFAULT(ENUM_GET(gds_LineStyle, Solid)), uint32_t fillStyle GDS_DEFAULT(ENUM_GET(gds_FillStyle, None)));
void GDS_Ellipse(int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t lineColour, uint32_t fillColour, uint8_t lineWidth GDS_DEFAULT(1), uint32_t lineStyle GDS_DEFAULT(ENUM_GET(gds_LineStyle, Solid)), uint32_t fillStyle GDS_DEFAULT(ENUM_GET(gds_FillStyle, None)));
void GDS_Arc(int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t a1, uint32_t a2, uint32_t lineColour, uint32_t fillColour, uint8_t lineWidth GDS_DEFAULT(1), uint32_t lineStyle GDS_DEFAULT(ENUM_GET(gds_LineStyle, Solid)), uint32_t fillStyle GDS_DEFAULT(ENUM_GET(gds_FillStyle, None)));
void GDS_Polygon(size_t points, gds_Point *pointData, bool closed,  uint32_t lineColour, uint32_t fillColour, uint8_t lineWidth GDS_DEFAULT(1), uint32_t lineStyle GDS_DEFAULT(ENUM_GET(gds_LineStyle, Solid)), uint32_t fillStyle GDS_DEFAULT(ENUM_GET(gds_FillStyle, None)));
void GDS_Text(int32_t x, int32_t y, const char *string, uint32_t fontID, uint32_t size, uint32_t colour, uint8_t style GDS_DEFAULT(ENUM_GET(gds_TextStyle, Normal)));
void GDS_Blit(uint64_t src, uint32_t srcX, uint32_t srcY, uint32_t srcW, uint32_t srcH, int32_t dstX, int32_t dstY, uint32_t dstW, uint32_t dstH, uint32_t scale GDS_DEFAULT(100), uint32_t flags GDS_DEFAULT(0));

#ifdef __cplusplus
}
#endif

#endif