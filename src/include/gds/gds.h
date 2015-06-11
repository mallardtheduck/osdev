#ifndef _GDS_H
#define _GDS_H

#include "../bt_enum.h"

#ifdef __cplusplus
	#include <cstdint>
	#include <cstddef>
#else
	#include <stdint.h>
	#include <stddef.h>
#endif

#define FONT_NAME_MAX 255

ENUM_START(gds_MsgType)
	ENUM_SET(gds_MsgType, Info, 			0),
	ENUM_SET(gds_MsgType, NewSurface, 		1),
	ENUM_SET(gds_MsgType, DeleteSurface,	2),
	ENUM_SET(gds_MsgType, SelectSurface, 	3),
	ENUM_SET(gds_MsgType, AddDrawingOp, 	4),
	ENUM_SET(gds_MsgType, RemoveDrawingOp, 	5),
	ENUM_SET(gds_MsgType, GetDrawingOp, 	6),
	ENUM_SET(gds_MsgType, SurfaceInfo, 		7),
	ENUM_SET(gds_MsgType, SetScale, 		8),
	ENUM_SET(gds_MsgType, GetColour, 		9),
		
	ENUM_SET(gds_MsgType, SelectScreen,		100),
	ENUM_SET(gds_MsgType, UpdateScreen, 	101),
	ENUM_SET(gds_MsgType, SetScreenMode,	102),
	
	ENUM_SET(gds_MsgType, Shutdown,			999),
ENUM_END
ENUM_TYPE(gds_MsgType);

ENUM_START(gds_DrawingOpType)
	ENUM_SET(gds_DrawingOpType, Dot, 		0),
	ENUM_SET(gds_DrawingOpType, Line, 		1),
	ENUM_SET(gds_DrawingOpType, Box, 		2),
	ENUM_SET(gds_DrawingOpType, Ellipse,	3),
	ENUM_SET(gds_DrawingOpType, Arc, 		4),
	ENUM_SET(gds_DrawingOpType, Polygon, 	5),
	//ENUM_SET(gds_DrawingOpType, Spline, 	6),
	ENUM_SET(gds_DrawingOpType, Text, 		10),
	
	ENUM_SET(gds_DrawingOpType, None, 		-1),
ENUM_END
ENUM_TYPE(gds_DrawingOpType);

ENUM_START(gds_ColourType)
	ENUM_SET(gds_ColourType, Indexed, 	0),
	ENUM_SET(gds_ColourType, True, 		1),
ENUM_END
ENUM_TYPE(gds_ColourType);

ENUM_START(gds_FontStyle)
	ENUM_SET(gds_FontStyle, Normal, 0),
	ENUM_SET(gds_FontStyle, Bold, 	1 << 0),
	ENUM_SET(gds_FontStyle, Italic, 1 << 1),
ENUM_END
ENUM_TYPE(gds_FontStyle);

ENUM_START(gds_TextStyle)
	ENUM_SET(gds_TextStyle, Normal, 		0),
	ENUM_SET(gds_TextStyle, Underline, 		1 << 0),
	ENUM_SET(gds_TextStyle, Strikethrough, 	1 << 1),
ENUM_END
ENUM_TYPE(gds_TextStyle);

ENUM_START(gds_SurfaceType)
	ENUM_SET(gds_SurfaceType, Bitmap, 	0),
	ENUM_SET(gds_SurfaceType, Vector, 	1),
	ENUM_SET(gds_SurfaceType, Memory, 	2),
	ENUM_SET(gds_SurfaceType, Screen, 	100),
	
	ENUM_SET(gds_SurfaceType, None, 	-1),
ENUM_END
ENUM_TYPE(gds_SurfaceType);

ENUM_START(gds_LineStyle)
	ENUM_SET(gds_LineStyle, Default, 0),
ENUM_END
ENUM_TYPE(gds_LineStyle);

ENUM_START(gds_FillStyle)
	ENUM_SET(gds_FillStyle, Default, 0),
ENUM_END
ENUM_TYPE(gds_FillStyle);

struct gds_Colour{
	ENUM_NAME(gds_ColourType) type;
	union{
		uint8_t indexedColour;
		uint32_t trueColour;
	};
};
#ifndef __cplusplus
typedef struct gds_Colour gds_Colour;
#endif

struct gds_DrawingOp {
	ENUM_NAME(gds_DrawingOpType) type;
	union{
		struct{
			uint32_t x, y;
		} Dot;
		struct{
			uint32_t x1, y1, x2, y2;
		} Line;
		struct{
			uint32_t x, y, w, h;
		} Box;
		struct{
			uint32_t x, y, w, h;
		} Ellipse;
		struct{
			uint32_t x, y, w, h, a1, a2;
		} Arc;
		struct{
			size_t points;
			bool closed;
		} Polygon;
		/*struct{
			size_t points;
		} Spline;*/
		struct{
			size_t chars;
			uint32_t fontID;
			uint32_t size;
			uint8_t style;
		} Text;
	};
	struct{
		uint32_t lineStyle;
		gds_Colour lineColour;
		uint32_t fillStyle;
		gds_Colour fillColour;
		uint8_t lineWidth;
	} Common;
};
#ifndef __cplusplus
typedef struct gds_DrawingOp gds_DrawingOp;
#endif

struct gds_FontInfo{
	uint32_t fontID;
	char name[FONT_NAME_MAX];
	uint8_t fontStyle;
};
#ifndef __cplusplus
typedef struct gds_FontInfo gds_FontInfo;
#endif

struct gds_SurfaceInfo{
	uint64_t id;
	ENUM_NAME(gds_SurfaceType) type;
	uint32_t w, h, scale;
	ENUM_NAME(gds_ColourType) colourType;
};
#ifndef __cplusplus
typedef struct gds_SurfaceInfo gds_SurfaceInfo;
#endif

struct gds_Info{
	uint32_t version;
	size_t surfaceCount;
	size_t clientCount;
};
#ifndef __cplusplus
typedef struct gds_Info gds_Info;
#endif

struct gds_ScreenUpdateRect{
	uint32_t x, y, w, h;
};
#ifndef __cplusplus
typedef struct gds_ScreenUpdateRect gds_ScreenUpdateRect;
#endif

struct gds_Point{
	uint32_t x, y;
};
#ifndef __cplusplus
typedef struct gds_Point gds_Point;
#endif

struct gds_TrueColour{
	uint32_t r, g, b;
};
#ifndef __cplusplus
typedef struct gds_TrueColour gds_TrueColour;
#endif

#endif