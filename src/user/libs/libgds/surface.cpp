#include <gds/surface.hpp>
#include <gds/libgds.h>

using namespace std;

namespace btos_api{
namespace gds{

	Surface::Surface(gds_SurfaceType::Enum type, uint32_t w, uint32_t h, uint32_t scale, uint32_t colourType, uint64_t shmRegion, size_t shmOffset){
		gds_id = GDS_NewSurface(type, w, h, scale, colourType, shmRegion, shmOffset);
		owned = true;
	}
	
	Surface::Surface(Surface &&s){
		gds_id = s.gds_id;
		owned = s.owned;
		s.gds_id = 0;
		s.owned = false;
	}

	Surface::~Surface(){
		Select();
		if(gds_id && owned) GDS_DeleteSurface();
	}

	Surface Surface::Wrap(uint64_t id, bool own){
		Surface ret;
		ret.gds_id = id;
		ret.owned = own;
		return ret;
	}

	void Surface::Select() const{
		GDS_SelectSurface(gds_id);
	}

	uint64_t Surface::GetID() const{
		return gds_id;
	}

	uint32_t Surface::AddDrawingOp(gds_DrawingOp op){
		Select();
		return GDS_AddDrawingOp(op);
	}

	vector<uint32_t> Surface::AddDrawingOps(const vector<gds_DrawingOp> &ops){
		Select();
		vector<uint32_t> ret(ops.size());
		GDS_MultiDrawingOps(ops.size(), const_cast<gds_DrawingOp*>(ops.data()), ret.data());
		return ret;
	}
	void Surface::RemoveDrawingOp(uint32_t index){
		Select();
		GDS_RemoveDrawingOp(index);
	}
	gds_DrawingOp Surface::GetDrawingOp(uint32_t index) const{
		Select();
		return GDS_GetDrawingOp(index);
	}
	void Surface::ReorderOp(uint32_t op, uint32_t ref, gds_ReorderMode::Enum mode){
		Select();
		GDS_ReorderOp(op, ref, mode);
	}
	void Surface::SetOpParameters(const gds_OpParameters *params){
		Select();
		GDS_SetOpParameters(params);
	}
	
	gds_SurfaceInfo Surface::Info() const{
		Select();
		return GDS_SurfaceInfo();
	}
	
	void Surface::SetScale(uint32_t scale){
		Select();
		GDS_SetScale(scale);
	}
	uint32_t Surface::GetScale() const{
		Select();
		return Info().scale;
	}

	Colour Surface::GetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) const{
		Select();
		return {GDS_GetColour(r, g, b, a), r, g, b, a};
	}

	uint32_t Surface::Dot(const Point &p, const Colour &c, uint8_t size){
		Select();
		return GDS_Dot(p.x, p.y, c.id, size);
	}
	uint32_t Surface::Line(const Point &p1, const Point &p2, const Colour &c, uint8_t width, uint32_t style){
		Select();
		return GDS_Line(p1.x, p1.y, p2.x, p2.y, c.id, width, style);
	}
	uint32_t Surface::Box(const Rect &r, const Colour &lineColour, const Colour &fillColour, uint8_t lineWidth, uint32_t lineStyle, uint32_t fillStyle){
		Select();
		return GDS_Box(r.x, r.y, r.w, r.h, lineColour.id, fillColour.id, lineWidth, lineStyle, fillStyle);
	}
	uint32_t Surface::Ellipse(const Rect &r, const Colour &lineColour, const Colour &fillColour, uint8_t lineWidth, uint32_t lineStyle, uint32_t fillStyle){
		Select();
		return GDS_Ellipse(r.x, r.y, r.w, r.h, lineColour.id, fillColour.id, lineWidth, lineStyle, fillStyle);
	}
	uint32_t Surface::Arc(const Rect &r, uint32_t a1, uint32_t a2, const Colour &lineColour, const Colour &fillColour, uint8_t lineWidth, uint32_t lineStyle, uint32_t fillStyle){
		Select();
		return GDS_Arc(r.x, r.y, r.w, r.h, a1, a2, lineColour.id, fillColour.id, lineWidth, lineStyle, fillStyle);
	}
	uint32_t Surface::Polygon(const std::vector<Point> &points, bool closed, const Colour &lineColour, const Colour &fillColour, uint8_t lineWidth, uint32_t lineStyle, uint32_t fillStyle){
		Select();
		return GDS_Polygon(points.size(), const_cast<Point*>(points.data()), closed, lineColour.id, fillColour.id, lineWidth, lineStyle, fillStyle);
	}
	uint32_t Surface::Text(const Point &p, const std::string &text, const Font &font, uint32_t size, const Colour &c, uint8_t style){
		Select();
		return GDS_Text(p.x, p.y, text.c_str(), font.id, size, c.id, style);
	}
	uint32_t Surface::TextChar(const Point &p, char c, const Font &font, uint32_t size, const Colour &col, uint8_t style){
		Select();
		return GDS_TextChar(p.x, p.y, c, font.id, size, col.id, style);
	}
	uint32_t Surface::Blit(const Surface &src, const Rect &srcRect, const Rect &dstRect, uint32_t scale, uint32_t flags){
		Select();
		return GDS_Blit(src.gds_id, srcRect.x, srcRect.y, srcRect.w, srcRect.h, dstRect.x, dstRect.y, dstRect.w, dstRect.h, scale, flags);
	}

}
}
