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
	ENUM_SET(gds_MsgType, GetSurface, 		2),
	ENUM_SET(gds_MsgType, DeleteSurface,	3),
	ENUM_SET(gds_MsgType, SelectSurface, 	4),
	ENUM_SET(gds_MsgType, AddDrawingOp, 	5),
	ENUM_SET(gds_MsgType, RemoveDrawingOp, 	6),
	ENUM_SET(gds_MsgType, GetDrawingOp, 	7),
	ENUM_SET(gds_MsgType, SurfaceInfo, 		8),
	ENUM_SET(gds_MsgType, SetScale, 		9),
		
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

ENUM_START(gds_SurfaceType)
	ENUM_SET(gds_SurfaceType, Bitmap, 	0),
	ENUM_SET(gds_SurfaceType, Vector, 	1),
	ENUM_SET(gds_SurfaceType, Memory, 	2),
	ENUM_SET(gds_SurfaceType, Screen, 	100),
	
	ENUM_SET(gds_SurfaceType, None, 	-1),
ENUM_END
ENUM_TYPE(gds_SurfaceType)

struct DrawingOp {
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
			bool filled;
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
		ENUM_NAME(gds_ColourType) lineColourType;
		uint32_t lineStyle;
		union{
			uint32_t lineTrueColour;
			uint8_t lineIndexedColour;
		};
		ENUM_NAME(gds_ColourType) fillColourType;
		uint32_t fillStyle;
		union{
			uint32_t fillTrueColour;
			uint8_t fillIndexedColour;
		};
		uint8_t lineWidth;
	} Common;
};

struct gds_FontInfo{
	uint32_t fontID;
	char name[FONT_NAME_MAX];
	uint8_t fontStyle;
};

struct gds_SurfaceInfo{
	uint64_t id;
	ENUM_NAME(gds_SurfaceType) type;
	uint32_t w, h, scale;
	ENUM_NAME(gds_ColourType) colourType;
};

struct gds_Info{
	uint32_t version;
	size_t surfaceCount;
	size_t clientCount;
};

struct gds_ScreenUpdateRect{
	uint32_t x, y, w, h;
};

#endif