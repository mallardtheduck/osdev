#include "vector_surface.hpp"
#include "bitmap_surface.hpp"
#include <gd.h>
#include <dev/rtc.h>

using namespace std;

static const size_t ZUnspecified = SIZE_MAX;

VectorSurface::VectorSurface(size_t w, size_t h, bool i, uint32_t /*scale*/) : width(w), height(h), indexed(i) {}

VectorSurface::~VectorSurface() {}

size_t VectorSurface::AddOperation(gds_DrawingOp op){
	uint32_t id = ++opCounter;
	while(ops.find(id) != ops.end()) id = ++opCounter;
	ops.insert({id, {ZUnspecified, op, NULL}});
	cache.reset();
	OrderOps();
	return id;
}

void VectorSurface::RemoveOperation(size_t id){
	if(ops.find(id) != ops.end()){
		ops.erase(id);
		cache.reset();
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
	return indexed ? 8 : 32;
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
		cache.reset();
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
	indexed = i;
}

std::shared_ptr<GD::Image> VectorSurface::Render(uint32_t /*scale*/){
	if(!cache){
		uint64_t start = bt_rtc_millis();
		OrderOps();
		vector<VectorOp> sops;
		for(const auto &op : ops){
			sops.push_back(op.second);
		}
		sort(sops.begin(), sops.end(), [](const VectorOp &a, const VectorOp &b){return a.zOrder < b.zOrder;});
		BitmapSurface bsurf(width, height, indexed);
		for(const auto &op : sops){
			gds_DrawingOp dop = op.op;
			shared_ptr<gds_OpParameters> p;
			if(dop.type == gds_DrawingOpType::Text || dop.type == gds_DrawingOpType::Polygon){
				if(op.params) p = op.params;
				else{
					bt_zero("GDS: Params missing for operation. Skipping.\n");
					continue;
				}
			}
			uint32_t lineColour = bsurf.GetColour(gdTrueColorGetRed(dop.Common.lineColour), gdTrueColorGetGreen(dop.Common.lineColour), gdTrueColorGetBlue(dop.Common.lineColour), gdTrueColorGetAlpha(dop.Common.lineColour));
			uint32_t fillColour = bsurf.GetColour(gdTrueColorGetRed(dop.Common.fillColour), gdTrueColorGetGreen(dop.Common.fillColour), gdTrueColorGetBlue(dop.Common.fillColour), gdTrueColorGetAlpha(dop.Common.fillColour));
			dop.Common.lineColour = lineColour;
			dop.Common.fillColour = fillColour;
			bsurf.AddOperation(dop);
			if(p) bsurf.SetOpParameters(p);
		}
		cache = bsurf.Render(100);
		uint64_t end = bt_rtc_millis();
		stringstream ss;
		ss << "GDS: Vector surface rendered in " << end - start << "ms." << endl;
		bt_zero(ss.str().c_str());
	}
	return cache;
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
	cache.reset();
}
