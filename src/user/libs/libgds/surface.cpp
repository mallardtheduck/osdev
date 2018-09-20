#include <gds/surface.hpp>
#include <gds/libgds.h>

using namespace std;

namespace btos_api{
namespace gds{
	
	Surface::QueueItem::QueueItem(QueueItemType type) : itemType(type){
		if(type == OpList){
			new(&opList) vector<gds_DrawingOp>();
		}else if(type == ParamOp){
			new(&paramOp) decltype(paramOp);
		}
	}

	Surface::QueueItem::~QueueItem(){
		if(itemType == OpList){
			opList.~vector<gds_DrawingOp>();
		}else if(itemType == ParamOp){
			paramOp.params.~unique_ptr<gds_OpParameters>();
		}
	}
	
	Surface::QueueItem::QueueItem(QueueItem &&other){
		*this = move(other);
	}
	
	Surface::QueueItem &Surface::QueueItem::operator=(QueueItem &&other){
		itemType = other.itemType;
		other.itemType = Destroyed;
		if(itemType == OpList){
			new(&opList) vector<gds_DrawingOp>(move(other.opList));
		}else if(itemType == ParamOp){
			new(&paramOp) decltype(paramOp)(move(other.paramOp));
		}
		return *this;
	}

	Surface::Surface(gds_SurfaceType::Enum type, uint32_t w, uint32_t h, uint32_t scale, uint32_t colourType, uint64_t shmRegion, size_t shmOffset){
		gds_id = GDS_NewSurface(type, w, h, scale, colourType, shmRegion, shmOffset);
		owned = true;
		queued = false;
	}
	
	Surface::Surface(Surface &&s){
		gds_id = s.gds_id;
		owned = s.owned;
		s.gds_id = 0;
		s.owned = false;
		queued = false;
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
		uint32_t key = r | g << 8 | b << 16 | a << 24;
		auto i = colourCache.find(key);
		if(i != colourCache.end()) return i->second;
		else{
			Select();
			Colour ret {GDS_GetColour(r, g, b, a), r, g, b, a};
			colourCache[key] = ret;
			return ret;
		}
	}

	uint32_t Surface::Dot(const Point &p, const Colour &c, uint8_t size){
		Select();
		if(queued) QueueOp(GDS_Dot_Op(p.x, p.y, c.id, size));
		else return GDS_Dot(p.x, p.y, c.id, size);
		return 0;
	}
	uint32_t Surface::Line(const Point &p1, const Point &p2, const Colour &c, uint8_t width, uint32_t style){
		Select();
		if(queued) QueueOp(GDS_Line_Op(p1.x, p1.y, p2.x, p2.y, c.id, width, style));
		else return GDS_Line(p1.x, p1.y, p2.x, p2.y, c.id, width, style);
		return 0;
	}
	uint32_t Surface::Box(const Rect &r, const Colour &lineColour, const Colour &fillColour, uint8_t lineWidth, uint32_t lineStyle, uint32_t fillStyle){
		Select();
		if(queued) QueueOp(GDS_Box_Op(r.x, r.y, r.w, r.h, lineColour.id, fillColour.id, lineWidth, lineStyle, fillStyle));
		else return GDS_Box(r.x, r.y, r.w, r.h, lineColour.id, fillColour.id, lineWidth, lineStyle, fillStyle);
		return 0;
	}
	uint32_t Surface::Ellipse(const Rect &r, const Colour &lineColour, const Colour &fillColour, uint8_t lineWidth, uint32_t lineStyle, uint32_t fillStyle){
		Select();
		if(queued) QueueOp(GDS_Ellipse_Op(r.x, r.y, r.w, r.h, lineColour.id, fillColour.id, lineWidth, lineStyle, fillStyle));
		else return GDS_Ellipse(r.x, r.y, r.w, r.h, lineColour.id, fillColour.id, lineWidth, lineStyle, fillStyle);
		return 0;
	}
	uint32_t Surface::Arc(const Rect &r, uint32_t a1, uint32_t a2, const Colour &lineColour, const Colour &fillColour, uint8_t lineWidth, uint32_t lineStyle, uint32_t fillStyle){
		Select();
		if(queued) QueueOp(GDS_Arc_Op(r.x, r.y, r.w, r.h, a1, a2, lineColour.id, fillColour.id, lineWidth, lineStyle, fillStyle));
		else return GDS_Arc(r.x, r.y, r.w, r.h, a1, a2, lineColour.id, fillColour.id, lineWidth, lineStyle, fillStyle);
		return 0;
	}
	uint32_t Surface::Polygon(const std::vector<Point> &points, bool closed, const Colour &lineColour, const Colour &fillColour, uint8_t lineWidth, uint32_t lineStyle, uint32_t fillStyle){
		Select();
		if(queued){
			auto op = GDS_Polygon_Op(closed, lineColour.id, fillColour.id, lineWidth, lineStyle, fillStyle);
			auto params = GDS_Polygon_Params(0, points.size(), const_cast<Point*>(points.data()));
			QueueOp(op, params);
		}else return GDS_Polygon(points.size(), const_cast<Point*>(points.data()), closed, lineColour.id, fillColour.id, lineWidth, lineStyle, fillStyle);
		return 0;
	}
	uint32_t Surface::Text(const Point &p, const std::string &text, const Font &font, uint32_t size, const Colour &c, uint8_t style){
		Select();
		if(queued){
			auto op = GDS_Text_Op(p.x, p.y, font.id, size, c.id, style);
			auto params = GDS_Text_Params(0, text.c_str());
			QueueOp(op, params);
		}else return GDS_Text(p.x, p.y, text.c_str(), font.id, size, c.id, style);
		return 0;
	}
	uint32_t Surface::TextChar(const Point &p, char c, const Font &font, uint32_t size, const Colour &col, uint8_t style){
		Select();
		if(queued) QueueOp(GDS_TextChar_Op(p.x, p.y, c, font.id, size, col.id, style));
		else return GDS_TextChar(p.x, p.y, c, font.id, size, col.id, style);
		return 0;
	}
	uint32_t Surface::Blit(const Surface &src, const Rect &srcRect, const Rect &dstRect, uint32_t scale, uint32_t flags){
		Select();
		if(queued) QueueOp(GDS_Blit_Op(src.gds_id, srcRect.x, srcRect.y, srcRect.w, srcRect.h, dstRect.x, dstRect.y, dstRect.w, dstRect.h, scale, flags));
		else return GDS_Blit(src.gds_id, srcRect.x, srcRect.y, srcRect.w, srcRect.h, dstRect.x, dstRect.y, dstRect.w, dstRect.h, scale, flags);
		return 0;
	}

	void Surface::BeginQueue(){
		queue.clear();
		queued = true;
	}
	
	void Surface::CommitQueue(){
		for(auto &qi : queue){
			if(qi.itemType == OpList) AddDrawingOps(qi.opList);
			else if(qi.itemType == ParamOp){
				auto id = AddDrawingOp(qi.paramOp.op);
				qi.paramOp.params->op_id = id;
				SetOpParameters(qi.paramOp.params.get());
			}
		}
		queue.clear();
		queued = false;
	}
	
	void Surface::CancelQueue(){
		queue.clear();
		queued = false;
	}
	
	void Surface::QueueOp(const gds_DrawingOp &op, gds_OpParameters *params){
		if(params){
			QueueItem it(ParamOp);
			it.paramOp.op = op;
			it.paramOp.params.reset(params);
			queue.push_back(move(it));
		}else{
			if(queue.empty() || queue.back().itemType != OpList){
				QueueItem nit(OpList);
				queue.push_back(move(nit));
			}
			auto &it = queue.back();
			it.opList.push_back(move(op));
		}
	}
}
}
