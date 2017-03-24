#include "vector_surface.hpp"
#include "bitmap_surface.hpp"
#include <gd.h>

using namespace std;

VectorSurface::VectorSurface(size_t w, size_t h, bool i, uint32_t /*scale*/) : width(w), height(h), indexed(i) {}

VectorSurface::~VectorSurface() {}

size_t VectorSurface::AddOperation(gds_DrawingOp op){
	uint32_t id = ++opCounter;
	while(ops.find(id) != ops.end()) id = ++opCounter;
	ops.insert({id, op});
	cache.reset();
	return id;
}

void VectorSurface::RemoveOperation(size_t id){
	if(ops.find(id) != ops.end()){
		ops.erase(id);
		cache.reset();
	}
	if(params.find(id) != params.end()) params.erase(id);
}

gds_DrawingOp VectorSurface::GetOperation(size_t id){
	if(ops.find(id) != ops.end()) return ops[id];
	
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
		params.insert({p->op_id, p});
		cache.reset();
	}
}

std::shared_ptr<gds_OpParameters> VectorSurface::GetOpParameters(uint32_t op){
	if(params.find(op) != params.end()) return params[op];
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
		BitmapSurface bsurf(width, height, indexed);
		for(auto &op : ops){
			shared_ptr<gds_OpParameters> p;
			if(op.second.type == gds_DrawingOpType::Text || op.second.type == gds_DrawingOpType::Polygon){
				if(params.find(op.first) != params.end()) p = params[op.first];
				else{
					bt_zero("GDS: Params missing for operation. Skipping.\n");
					continue;
				}
			}
			uint32_t lineColour = bsurf.GetColour(gdTrueColorGetRed(op.second.Common.lineColour), gdTrueColorGetGreen(op.second.Common.lineColour), gdTrueColorGetBlue(op.second.Common.lineColour), gdTrueColorGetAlpha(op.second.Common.lineColour));
			uint32_t fillColour = bsurf.GetColour(gdTrueColorGetRed(op.second.Common.fillColour), gdTrueColorGetGreen(op.second.Common.fillColour), gdTrueColorGetBlue(op.second.Common.fillColour), gdTrueColorGetAlpha(op.second.Common.fillColour));
			op.second.Common.lineColour = lineColour;
			op.second.Common.fillColour = fillColour;
			bsurf.AddOperation(op.second);
			if(p) bsurf.SetOpParameters(p);
		}
		cache = bsurf.Render(100);
	}
	return cache;
}
