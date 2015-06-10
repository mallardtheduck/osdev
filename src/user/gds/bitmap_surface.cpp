#include "bitmap_surface.hpp"
#include "drawingop.hpp"

BitmapSurface::BitmapSurface(size_t w, size_t h, bool indexed, uint32_t scale){
	if(indexed) {
		image = new GD::Image((int)w, (int)h, !indexed);
	}
	this->scale = scale;
}

size_t BitmapSurface::AddOperation(DrawingOp op) {
	switch(op.type){
		case gds_DrawingOpType::Dot:
			image->SetPixel(op.Dot.x, op.Dot.y, op.Common.lineIndexedColour);
			break;

		case gds_DrawingOpType::Line:
			image->Line(op.Line.x1, op.Line.y1, op.Line.x2, op.Line.y2, op.Common.lineIndexedColour);
			break;

		case gds_DrawingOpType::Box:
			if(op.Common.fillStyle > 0){
				image->FilledRectangle(op.Box.x, op.Box.y, op.Box.x + op.Box.w, op.Box.y + op.Box.h, op.Common.fillIndexedColour);
			}
			image->Rectangle(op.Box.x, op.Box.y, op.Box.x + op.Box.w, op.Box.y + op.Box.h, op.Common.lineIndexedColour);
			break;

		case gds_DrawingOpType::Ellipse:
			if(op.Common.fillStyle > 0){
				image->FilledEllipse(op.Ellipse.x, op.Ellipse.y, op.Ellipse.w, op.Ellipse.h, op.Common.fillIndexedColour);
			}
			image->Ellipse(op.Ellipse.x, op.Ellipse.y, op.Ellipse.w, op.Ellipse.h, op.Common.lineIndexedColour);
			break;

		case gds_DrawingOpType::Arc:
			if(op.Common.fillStyle > 0){
				image->FilledArc(op.Arc.x, op.Arc.y, op.Arc.w, op.Arc.h, op.Arc.a1, op.Arc.a2, op.Common.fillIndexedColour, 0);
			}
			image->Arc(op.Arc.x, op.Arc.y, op.Arc.w, op.Arc.h, op.Arc.a1, op.Arc.a2, op.Common.lineIndexedColour);

		default:
			break;

	}
	return 0;
}

void BitmapSurface::RemoveOperation(size_t /*id*/) {
	//Does nothing on bitmap surface.
}

DrawingOp BitmapSurface::GetOperation(size_t /*id*/){
	DrawingOp ret;
	ret.type = gds_DrawingOpType::None;
	return ret;
}

size_t BitmapSurface::GetWidth() {
	return (size_t)image->Width();
}

size_t BitmapSurface::GetHeight() {
	return (size_t)image->Height();
}

size_t BitmapSurface::GetDepth() {
	return image->IsTrueColor() ? 32 : 8;
}

void BitmapSurface::Resize(size_t w, size_t h, bool indexed) {
	delete image;
	image = new GD::Image((int)w, (int)h, !indexed);
}

uint32_t BitmapSurface::GetScale(){
	return scale;
}

void BitmapSurface::SetScale(uint32_t scale){
	this->scale = scale;
}

gds_SurfaceType::Enum BitmapSurface::GetType(){
	return gds_SurfaceType::Bitmap;
}

BitmapSurface::~BitmapSurface() {
	delete image;
}