#include "vector_surface.hpp"
#include "bitmap_surface.hpp"
#include "graphics.hpp"
#include "fonts.hpp"
#include <gd.h>
#include <dev/rtc.h>
#include <util/lrucache.hpp>

#include <limits>

using namespace std;

static uint64_t cacheIdCounter = 0;
static const size_t ZUnspecified = SIZE_MAX;

static cache::lru_cache<uint64_t, std::shared_ptr<BitmapSurface>> renderCache(128);

bool operator==(const VectorSurface::Rectangle &r1, const VectorSurface::Rectangle &r2){
	return r1.x == r2.x && r1.y == r2.y && r1.w == r2.w && r1.h == r2.h;
}

bool operator!=(const VectorSurface::Rectangle &r1, const VectorSurface::Rectangle &r2){
	return !(r1 == r2);
}

bool VectorSurface::Contains(const Rectangle &outer, const Rectangle &inner){
	if(outer == inner) return true;
	return (InRect(inner.x, inner.y, outer) && InRect(inner.x + inner.w, inner.y + inner.h, outer));
}

bool VectorSurface::InRect(int32_t x, int32_t y, const Rectangle &r){
	if(x >= r.x && x < (r.x + (int32_t)r.w) && y >= r.y && y < (r.y + (int32_t)r.h)) return true;
	else return false;
}

bool VectorSurface::Overlaps(const VectorSurface::Rectangle &r1, const VectorSurface::Rectangle &r2){
	return !(r1.x + (int32_t)r1.w - 1 < r2.x || r1.y + (int32_t)r1.h - 1 < r2.y || r1.x > r2.x + (int32_t)r2.w - 1 || r1.y > r2.y + (int32_t)r2.h - 1);
}

bool VectorSurface::OpInRect(const VectorOp &vop, const VectorSurface::Rectangle &rect){
	auto &op = vop.op;
	switch(op.type){
		case gds_DrawingOpType::Dot:
			return InRect(op.Dot.x, op.Dot.y, rect);
		case gds_DrawingOpType::Line:{
			int32_t x1 = op.Line.x1;
			int32_t y1 = op.Line.y1;
			int32_t x2 = op.Line.x2;
			int32_t y2 = op.Line.y2;
			if(x1 > x2) std::swap(x1, x2);
			if(y1 > y2) std::swap(y1, y2);
			return Overlaps({x1, y1, (uint32_t)(x2 - x1) + 1, (uint32_t)(y2 - y1) + 1}, rect);
		}
		case gds_DrawingOpType::Box:
			return Overlaps({op.Box.x, op.Box.y, op.Box.w, op.Box.h}, rect);
		case gds_DrawingOpType::Polygon:{
			int32_t minX = std::numeric_limits<int32_t>::max();
			int32_t minY = std::numeric_limits<int32_t>::max();
			int32_t maxX = 0;
			int32_t maxY = 0;
			
			size_t pointCount = vop.params->size / sizeof(gds_Point);
			for(size_t i =0; i<pointCount; ++i){
				int32_t x = ((gds_Point*)vop.params->data)[i].x;
				int32_t y = ((gds_Point*)vop.params->data)[i].y;
				if(x < minX) minX = x;
				if(x > maxX) maxX = x;
				if(y < minY) minY = y;
				if(y > maxY) maxY = y;
			}
			
			return Overlaps({minX, minY, (uint32_t)(maxX - minX), (uint32_t)(maxY - minY)}, rect);
		}
		case gds_DrawingOpType::Blit:
			return Overlaps({op.Blit.dstX, op.Blit.dstY, op.Blit.dstW, op.Blit.dstH}, rect);
		default: return true;
	}
}

std::shared_ptr<BitmapSurface> VectorSurface::GetCache(bool &created){
	if(cacheId && renderCache.exists(cacheId)){
		created = false;
		return renderCache.get(cacheId);
	}else{
		created = true;
		cacheId = ++cacheIdCounter;
		auto ret = make_shared<BitmapSurface>(width, height, colourType);
		renderCache.put(cacheId, ret);
		return ret;
	}
}

void VectorSurface::DropCache(){
	if(cacheId && renderCache.exists(cacheId)) renderCache.drop(cacheId);
}

VectorSurface::VectorSurface(size_t w, size_t h, uint32_t cT, uint32_t /*scale*/) : width(w), height(h), colourType(cT) {}

VectorSurface::~VectorSurface() {
	DropCache();
}

size_t VectorSurface::AddOperation(gds_DrawingOp op){
	uint32_t id = ++opCounter;
	while(ops.find(id) != ops.end()) id = ++opCounter;
	ops.insert({id, {ZUnspecified, op, NULL}});
	update = true;
	OrderOps();
	return id;
}

void VectorSurface::RemoveOperation(size_t id){
	if(ops.find(id) != ops.end()){
		ops.erase(id);
		update = true;
	}
}

gds_DrawingOp VectorSurface::GetOperation(size_t id){
	if(ops.find(id) != ops.end()) return ops[id].op;
	
	gds_DrawingOp ret;
	ret.type = gds_DrawingOpType::None;
	return ret;
}

size_t VectorSurface::GetWidth(){
	return width;
}

size_t VectorSurface::GetHeight(){
	return height;
}

size_t VectorSurface::GetDepth(){
	return (colourType & gds_ColourType::True) ? 32 : 8;
}

uint32_t VectorSurface::GetScale(){
	return 100;
}

void VectorSurface::SetScale(uint32_t /*scale*/){
}

gds_SurfaceType::Enum VectorSurface::GetType(){
	return gds_SurfaceType::Vector;
}

uint32_t VectorSurface::GetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
	a >>= 1;
	uint32_t colour = (a << 24) | (r << 16) | (g << 8) | b;
	return colour;
}

void VectorSurface::SetOpParameters(std::shared_ptr<gds_OpParameters> p){
	if(ops.find(p->op_id) != ops.end()){
		ops[p->op_id].params = p;
		update = true;
	}
}

std::shared_ptr<gds_OpParameters> VectorSurface::GetOpParameters(uint32_t op){
	if(ops.find(op) != ops.end()) return ops[op].params;
	auto ret = make_shared<gds_OpParameters>();
	ret->op_id = 0;
	ret->size = 0;
	return ret;
}
	
void VectorSurface::Resize(size_t w, size_t h, bool i){
	width = w;
	height = h;
	if(i){
		colourType &= ~gds_ColourType::True;
	}else{
		colourType |= gds_ColourType::True;
	}
}

std::shared_ptr<GD::Image> VectorSurface::Render(uint32_t /*scale*/){
	bool created;
	auto cache = GetCache(created);
	if(created || update || !Contains(cacheRect, renderRect)){
		OrderOps();
		vector<VectorOp> sops;
		for(const auto &op : ops){
			sops.push_back(op.second);
		}
		sort(sops.begin(), sops.end(), [](const VectorOp &a, const VectorOp &b){return a.zOrder < b.zOrder;});
		if(cache->GetWidth() != width || cache->GetHeight() != height){
			DropCache();
			cache = GetCache(created);
		}else cache->Clear();
		
		auto &bsurf = *cache;
		if(renderRect.w){
			bsurf.GetImage()->SetClip(renderRect.x, renderRect.y, renderRect.x + renderRect.w, renderRect.y + renderRect.h);
		}
		size_t opsRendered = 0;
		for(const auto &op : sops){
			if(renderRect.w && !OpInRect(op, renderRect)) continue;
			++opsRendered;
			gds_DrawingOp dop = op.op;
			shared_ptr<gds_OpParameters> p;
			if(dop.type == gds_DrawingOpType::Text || dop.type == gds_DrawingOpType::Polygon){
				if(op.params) p = op.params;
				else{
					bt_zero("GDS: Params missing for operation. Skipping.\n");
					continue;
				}
			}
			if(renderRect.w > 0 && dop.type == gds_DrawingOpType::Box){
				auto x1 = std::max(dop.Box.x, renderRect.x - 1);
				auto y1 = std::max(dop.Box.y, renderRect.y - 1);
				auto x2 = std::min((dop.Box.x + dop.Box.w), (renderRect.x + renderRect.w + 1));
				auto y2 = std::min((dop.Box.y + dop.Box.h), (renderRect.y + renderRect.h + 1));
				dop.Box.x = x1;
				dop.Box.y = y1;
				dop.Box.w = x2 - x1;
				dop.Box.h = y2 - y1;
			}
			uint32_t lineColour = bsurf.GetColour(gdTrueColorGetRed(dop.Common.lineColour), gdTrueColorGetGreen(dop.Common.lineColour), gdTrueColorGetBlue(dop.Common.lineColour), gdTrueColorGetAlpha(dop.Common.lineColour));
			uint32_t fillColour = bsurf.GetColour(gdTrueColorGetRed(dop.Common.fillColour), gdTrueColorGetGreen(dop.Common.fillColour), gdTrueColorGetBlue(dop.Common.fillColour), gdTrueColorGetAlpha(dop.Common.fillColour));
			dop.Common.lineColour = lineColour;
			dop.Common.fillColour = fillColour;
			bsurf.AddOperation(dop);
			if(p) bsurf.SetOpParameters(p);
		}
		cacheRect = renderRect;
		update = false;
	}
	return cache->Render(100);
}

void VectorSurface::RenderTo(std::shared_ptr<GD::Image> dst, int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY, uint32_t w, uint32_t h, uint32_t flags){
	renderRect = {srcX, srcY, w, h};
	std::shared_ptr<GD::Image> src = Render(100);
	renderRect = {0, 0, 0, 0};
	if(src) FastBlit(*src, *dst, srcX, srcY, dstX, dstY, w, h, flags);
}

void VectorSurface::OrderOps(){
	vector<uint32_t> vops;
	for(auto &op : ops){
		vops.push_back(op.first);
	}
	sort(vops.begin(), vops.end(), [this](uint32_t a, uint32_t b){return ops[a].zOrder < ops[b].zOrder;});
	size_t zCounter = 0;
	for(auto &vop: vops){
		zCounter += 2;
		ops[vop].zOrder = zCounter;
	}
}

void VectorSurface::ReorderOp(uint32_t op, uint32_t ref, gds_ReorderMode::Enum mode){
	if(ops.find(op) == ops.end()) return;
	OrderOps();
	VectorOp &vop = ops[op];
	switch(mode){
		case gds_ReorderMode::Front:
			vop.zOrder = SIZE_MAX;
			break;
		case gds_ReorderMode::Back:
			vop.zOrder = 0;
			break;
		case gds_ReorderMode::Swap:
			if(ops.find(ref) != ops.end()){
				size_t tmp = vop.zOrder;
				vop.zOrder = ops[ref].zOrder;
				ops[ref].zOrder = tmp;
			}
			break;
		case gds_ReorderMode::Above:
			if(ops.find(ref) != ops.end()){
				vop.zOrder = ops[ref].zOrder + 1;
			}
			break;
		case gds_ReorderMode::Below:
			if(ops.find(ref) != ops.end()){
				vop.zOrder = ops[ref].zOrder - 1;
			}
			break;
	}
	OrderOps();
	update = true;
}

void VectorSurface::Clear(){
	ops.clear();
	update = true;
}

std::unique_ptr<gds_TextMeasurements> VectorSurface::MeasureText(const gds_TextParameters &p, std::string text){
	return ::MeasureText(p, text);
}
