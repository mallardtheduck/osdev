#ifndef _GDS_H
#define _GDS_H

#include <util/bt_enum.h>

#ifdef __cplusplus
	#include <cstdint>
	#include <cstddef>
#else
	#include <stdint.h>
	#include <stddef.h>
	#include <stdbool.h>
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
	ENUM_SET(gds_MsgType, SetOpParameters,	10),
	ENUM_SET(gds_MsgType, GetOpParameters,	11),
	ENUM_SET(gds_MsgType, ReorderOp,		12),
	ENUM_SET(gds_MsgType, ClearSurface,		13),
	ENUM_SET(gds_MsgType, SetTextParameters,14),
	ENUM_SET(gds_MsgType, MeasureText,		15),
	
	ENUM_SET(gds_MsgType, GetFontID,		20),
	ENUM_SET(gds_MsgType, GetFontInfo,		21),
	ENUM_SET(gds_MsgType, GetGlyphInfo, 	22),
	ENUM_SET(gds_MsgType, GetMaxFontID,		23),
	
	ENUM_SET(gds_MsgType, MultiDrawingOps, 	30),
		
	ENUM_SET(gds_MsgType, SelectScreen,		100),
	ENUM_SET(gds_MsgType, UpdateScreen, 	101),
	ENUM_SET(gds_MsgType, SetScreenMode,	102),
	ENUM_SET(gds_MsgType, SetCursor,		103),
	ENUM_SET(gds_MsgType, CursorVisibility,	104),
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
	ENUM_SET(gds_DrawingOpType, TextChar,	11),
	ENUM_SET(gds_DrawingOpType, Blit,		12),
	
	ENUM_SET(gds_DrawingOpType, None, 		-1),
ENUM_END
ENUM_TYPE(gds_DrawingOpType);

ENUM_START(gds_ColourType)
	ENUM_SET(gds_ColourType, Indexed, 				0),
	ENUM_SET(gds_ColourType, True, 					1),
	ENUM_SET(gds_ColourType, AlphaEnable,			0),
	ENUM_SET(gds_ColourType, AlphaDisable,			2),
ENUM_END
ENUM_TYPE(gds_ColourType);

ENUM_START(gds_FontStyle)
	ENUM_SET(gds_FontStyle, Normal, 	0),
	ENUM_SET(gds_FontStyle, Bold, 		1),
	ENUM_SET(gds_FontStyle, Italic, 	2),
	ENUM_SET(gds_FontStyle, BoldItalic, 3),
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
	ENUM_SET(gds_LineStyle, Solid, 0),
ENUM_END
ENUM_TYPE(gds_LineStyle);

ENUM_START(gds_FillStyle)
	ENUM_SET(gds_FillStyle, None, 0),
	ENUM_SET(gds_FillStyle, Filled, 1),
ENUM_END
ENUM_TYPE(gds_FillStyle);

ENUM_START(gds_ReorderMode)
	ENUM_SET(gds_ReorderMode, Front, 0),
	ENUM_SET(gds_ReorderMode, Back, 1),
	ENUM_SET(gds_ReorderMode, Swap, 2),
	ENUM_SET(gds_ReorderMode, Above, 3),
	ENUM_SET(gds_ReorderMode, Below, 4),
ENUM_END
ENUM_TYPE(gds_ReorderMode);

struct gds_DrawingOp {
	ENUM_NAME(gds_DrawingOpType) type;
	union{
		struct{
			int32_t x, y;
		} Dot;
		struct{
			int32_t x1, y1, x2, y2;
		} Line;
		struct{
			int32_t x, y;
			uint32_t w, h;
		} Box;
		struct{
			int32_t x, y;
			uint32_t w, h;
		} Ellipse;
		struct{
			int32_t x, y;
			uint32_t w, h, a1, a2;
		} Arc;
		struct{
			bool closed;
		} Polygon;
		/*struct{
			size_t points;
		} Spline;*/
		struct{
			int32_t x, y;
			uint32_t fontID;
			uint32_t size;
		} Text;
		struct{
			int32_t x, y;
			uint32_t fontID;
			uint32_t size;
			char c;
		} TextChar;
		struct{
			uint64_t src;
			uint32_t srcX, srcY;
			uint32_t srcW, srcH;
			int32_t dstX, dstY;
			uint32_t dstW, dstH;
			uint32_t scale;
			uint32_t flags;
		} Blit;
	};
	struct{
		uint32_t lineStyle;
		uint32_t lineColour;
		uint32_t fillStyle;
		uint32_t fillColour;
		uint8_t lineWidth;
	} Common;
};
#ifndef __cplusplus
typedef struct gds_DrawingOp gds_DrawingOp;
#endif

struct gds_FontRequest{
	char name[FONT_NAME_MAX];
	uint8_t fontStyle;
};
#ifndef __cplusplus
typedef struct gds_FontRequest gds_FontRequest;
#endif

struct gds_FontInfo{
	uint32_t fontID;
	char name[FONT_NAME_MAX];
	uint8_t fontStyle;
	size_t scale;
	size_t maxW, maxH;
};
#ifndef __cplusplus
typedef struct gds_FontInfo gds_FontInfo;
#endif

struct gds_GlyphInfo{
	uint32_t fontID;
	size_t size;
	char ch;
	size_t w, h;
};
#ifndef __cplusplus
typedef struct gds_GlyphInfo gds_GlyphInfo;
#endif

struct gds_GlyphInfo_Request{
	uint32_t fontID;
	size_t size;
	char ch;
};
#ifndef __cplusplus
typedef struct gds_GlyphInfo_Request gds_GlyphInfo_Request;
#endif

struct gds_SurfaceInfo{
	uint64_t id;
	ENUM_NAME(gds_SurfaceType) type;
	uint32_t w, h, scale;
	uint32_t colourType;
	uint64_t shmRegion;
	size_t shmOffset;
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
	int32_t x, y;
};
#ifndef __cplusplus
typedef struct gds_Point gds_Point;
#endif

struct gds_TrueColour{
	uint8_t r, g, b, a;
};
#ifndef __cplusplus
typedef struct gds_TrueColour gds_TrueColour;
#endif

struct gds_CursorInfo{
	uint32_t hotx, hoty;
	uint64_t surfaceId;
};
#ifndef __cplusplus
typedef struct gds_CursorInfo gds_CursorInfo;
#endif

struct gds_OpParameters{
	ENUM_NAME(gds_DrawingOpType) type;
	uint32_t op_id;
	size_t size;
	char data[];
};
#ifndef __cplusplus
typedef struct gds_OpParameters gds_OpParameters;
#endif

struct gds_MultiOps{
	size_t count;
	gds_DrawingOp ops[];
};
#ifndef __cplusplus
typedef struct gds_MultiOps gds_MultiOps;
#endif

struct gds_ReorderOp{
	uint32_t op;
	uint32_t ref;
	ENUM_NAME(gds_ReorderMode) mode;
};
#ifndef __cplusplus
typedef struct gds_ReorderOp gds_ReorderOp;
#endif

struct gds_TextParameters{
	uint32_t fontID;
	uint32_t size;
};

#ifndef __cplusplus
typedef struct gds_TextParameters gds_TextParameters;
#endif

struct gds_TextMeasurements{
	uint32_t w;
	uint32_t h;
	size_t charCount;
	uint32_t charX[];
};

#ifndef __cplusplus
typedef struct gds_TextMeasurements gds_TextMeasurements;
#endif

#endif
