#ifndef _DRAWINGOP_HPP
#define _DRAWINGOP_HPP

#include <cstdint>
#include <cstddef>

enum class DrawingOpType{
	Dot		= 0,
	Line 	= 1,
	Box 	= 2,
	Ellipse	= 3,
	Arc		= 4,
	Polygon	= 5,
	Spline	= 6,
	Text	= 10,
};

enum class ColourType{
	Indexed = 0,
	True = 1,
};

struct DrawingOp {
	DrawingOpType type;
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
			uint32_t x, y, vr, wr;
		} Ellipse;
		struct{
			uint32_t x, y, vr, wr, a1, a2;
		} Arc;
		struct{
			size_t points;
			bool closed;
			bool filled;
		} Polygon;
		struct{
			size_t points;
		} Spline;
		struct{
			size_t chars;
			uint32_t fontID;
			uint32_t size;
			uint8_t style;
		} Text;
	};
	struct{
		ColourType lineColourType;
		union{
			uint32_t lineTrueColour;
			uint8_t lineIndexedColour;
		};
		ColourType fillColourType;
		union{
			uint32_t fillTrueColour;
			uint8_t fillIndexedColour;
		};
		uint8_t lineWidth;
	} Common;
};


#endif
