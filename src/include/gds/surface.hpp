#ifndef _SURFACE_HPP
#define _SURFACE_HPP

#include "gds.h"
#include "geom.hpp"
#include <vector>
#include <string>

namespace btos_api{
namespace gds{

	class Surface{
	protected:
		uint64_t gds_id;

		Surface(const Surface&) = delete;
		Surface operator=(const Surface&) = delete;
		Surface() {}
	public:
		Surface(gds_SurfaceType::Enum type, uint32_t w, uint32_t h, uint32_t scale = 100, gds_ColourType::Enum colourType = gds_ColourType::Indexed, uint64_t shmRegion = 0, size_t shmOffset = 0);

		Surface(Surface &&s);
		
		~Surface();

		virtual void Select() const;
		uint64_t GetID() const;

		uint32_t AddDrawingOp(gds_DrawingOp op);
		std::vector<uint32_t> AddDrawingOps(const std::vector<gds_DrawingOp> &ops);
		void RemoveDrawingOp(uint32_t index);
		gds_DrawingOp GetDrawingOp(uint32_t index) const;
		void ReorderOp(uint32_t op, uint32_t ref, gds_ReorderMode::Enum mode);
		void SetOpParameters(const gds_OpParameters *params);
		
		gds_SurfaceInfo Info() const;
		
		void SetScale(uint32_t scale);
		uint32_t GetScale() const;

		Colour GetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0);
		uint32_t Dot(const Point &p, const Colour &c, uint8_t size = 1);
		uint32_t Line(const Point &p1, const Point &p2, const Colour &c, uint8_t width = 1, uint32_t style = gds_LineStyle::Solid);
		uint32_t Box(const Rect &r, const Colour &lineColour, const Colour &fillColour, uint8_t lineWidth = 1, uint32_t lineStyle = gds_LineStyle::Solid, uint32_t fillStyle = gds_FillStyle::None);
		uint32_t Ellipse(const Rect &r, const Colour &lineColour, const Colour &fillColour, uint8_t lineWidth = 1, uint32_t lineStyle = gds_LineStyle::Solid, uint32_t fillStyle = gds_FillStyle::None);
		uint32_t Arc(const Rect &r, uint32_t a1, uint32_t a2, const Colour &lineColour, const Colour &fillColour, uint8_t lineWidth = 1, uint32_t lineStyle = gds_LineStyle::Solid, uint32_t fillStyle = gds_FillStyle::None);
		uint32_t Polygon(const std::vector<Point> &points, bool closed, const Colour &lineColour, const Colour &fillColour, uint8_t lineWidth = 1, uint32_t lineStyle = gds_LineStyle::Solid, uint32_t fillStyle = gds_FillStyle::None);
		uint32_t Text(const Point &p, const std::string &text, const Font &font, uint32_t size, const Colour &c, uint8_t style = gds_TextStyle::Normal);
		uint32_t TextChar(const Point &p, char c, const Font &font, uint32_t size, const Colour &col, uint8_t style = gds_TextStyle::Normal);
		uint32_t Blit(const Surface &src, const Rect &srcRect, const Rect &dstRect, uint32_t scale = 100, uint32_t flags = 0);
	};
	
}
}

#endif
