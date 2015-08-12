#include "bitmap_surface.hpp"
#include "drawingop.hpp"

#include <sstream>

BitmapSurface::BitmapSurface(size_t w, size_t h, bool indexed, uint32_t scale) {
	if(indexed) {
		image.reset(new GD::Image((int)w, (int)h, !indexed));
	}
	this->scale = scale;
	pending_op.type = gds_DrawingOpType::None;
}

size_t BitmapSurface::AddOperation(gds_DrawingOp op) {
	switch(op.type) {
		case gds_DrawingOpType::Dot:
			image->SetPixel(op.Dot.x, op.Dot.y, op.Common.lineColour);
			break;

		case gds_DrawingOpType::Line:
			image->Line(op.Line.x1, op.Line.y1, op.Line.x2, op.Line.y2, op.Common.lineColour);
			break;

		case gds_DrawingOpType::Box:
			if(op.Common.fillStyle > 0) {
				image->FilledRectangle(op.Box.x, op.Box.y, op.Box.x + op.Box.w, op.Box.y + op.Box.h, op.Common.fillColour);
			}
			image->Rectangle(op.Box.x, op.Box.y, op.Box.x + op.Box.w, op.Box.y + op.Box.h, op.Common.lineColour);
			break;

		case gds_DrawingOpType::Ellipse:
			if(op.Common.fillStyle > 0) {
				image->FilledEllipse(op.Ellipse.x, op.Ellipse.y, op.Ellipse.w, op.Ellipse.h, op.Common.fillColour);
			}
			image->Ellipse(op.Ellipse.x, op.Ellipse.y, op.Ellipse.w, op.Ellipse.h, op.Common.lineColour);
			break;

		case gds_DrawingOpType::Arc:
			if(op.Common.fillStyle > 0) {
				image->FilledArc(op.Arc.x, op.Arc.y, op.Arc.w, op.Arc.h, op.Arc.a1, op.Arc.a2, op.Common.fillColour, 0);
			}
			image->Arc(op.Arc.x, op.Arc.y, op.Arc.w, op.Arc.h, op.Arc.a1, op.Arc.a2, op.Common.lineColour);
			break;

		case gds_DrawingOpType::Blit: {
				auto srcSurface = allSurfaces[op.Blit.src].lock();
				if(srcSurface) {
					auto srcImage = srcSurface->Render(op.Blit.scale);
					image->CopyResized(srcImage->GetPtr(), op.Blit.dstX, op.Blit.dstY, op.Blit.srcX, op.Blit.srcY, op.Blit.dstW, op.Blit.dstH, op.Blit.srcW, op.Blit.srcH);
				}
			}
			break;
		case gds_DrawingOpType::Text:
		case gds_DrawingOpType::Polygon:
			pending_op = op;
			break;


		default:
			break;

	}
	return 0;
}

void BitmapSurface::RemoveOperation(size_t /*id*/) {
	//Does nothing on bitmap surface.
}

gds_DrawingOp BitmapSurface::GetOperation(size_t /*id*/) {
	gds_DrawingOp ret;
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
	image.reset(new GD::Image((int)w, (int)h, !indexed));
}

uint32_t BitmapSurface::GetScale() {
	return scale;
}

void BitmapSurface::SetScale(uint32_t scale) {
	this->scale = scale;
}

gds_SurfaceType::Enum BitmapSurface::GetType() {
	return gds_SurfaceType::Bitmap;
}

uint32_t BitmapSurface::GetColour(uint32_t r, uint32_t g, uint32_t b) {
	return (uint32_t) image->ColorResolve(r, g, b);
}

std::shared_ptr<GD::Image> BitmapSurface::Render(uint32_t scale) {
	if(scale == this->scale) return image;
	else return std::shared_ptr<GD::Image>();
}

void BitmapSurface::SetOpParameters(std::shared_ptr<gds_OpParameters> params){
	if(pending_op.type != gds_DrawingOpType::None && pending_op.type == params->type){
		switch(pending_op.type){
			case gds_DrawingOpType::Text:
				image->String(gdFontGetSmall(), pending_op.Text.x, pending_op.Text.y, params->data, pending_op.Common.lineColour);
				break;
			case gds_DrawingOpType::Polygon:
				{
					size_t pointCount = params->size / sizeof(gds_Point);
					gdPoint points[pointCount];
					for(size_t i =0; i<pointCount; ++i){
						std::stringstream ss;
						points[i].x = ((gds_Point*)params->data)[i].x;
						points[i].y = ((gds_Point*)params->data)[i].y;
						ss << "GDS: Polygon point " << i << " (" << points[i].x << ", " << points[i].y << ")" << std::endl;
						bt_zero(ss.str().c_str());
					}
					if(pending_op.Common.fillStyle == gds_FillStyle::Filled) image->FilledPolygon(points, pointCount, pending_op.Common.fillColour);
					if(pending_op.Polygon.closed) image->Polygon(points, pointCount, pending_op.Common.lineColour);
					else image->OpenPolygon(points, pointCount, pending_op.Common.lineColour);
					
				}
				break;
			default:
				break;
		}
		pending_op.type = gds_DrawingOpType::None;
	}
}

std::shared_ptr<gds_OpParameters> BitmapSurface::GetOpParameters(uint32_t){
	return std::shared_ptr<gds_OpParameters>();
}

BitmapSurface::~BitmapSurface() {
}
