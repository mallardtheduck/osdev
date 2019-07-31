#include "bitmap_surface.hpp"
#include "drawingop.hpp"
#include "fonts.hpp"

#include <sstream>
#include <gdfontmb.h>
#include <gdfontt.h>
#include <gdfontg.h>
#include <gdfontl.h>

#include <dev/rtc.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "graphics.hpp"

using namespace std;

BitmapSurface::BitmapSurface(size_t w, size_t h, uint32_t cT, uint32_t scale)
: colourType(cT)
{
	bool indexed = !(cT & gds_ColourType::True);
	image.reset(new GD::Image((int)w, (int)h, !indexed));
	this->scale = scale;
	pending_op.type = gds_DrawingOpType::None;
}

size_t BitmapSurface::AddOperation(gds_DrawingOp op) {
	//uint64_t op_start = bt_rtc_millis();
	image->SetThickness(op.Common.lineWidth);
	image->AlphaBlending(op.Common.fillStyle == gds_FillStyle::Overwrite ? gdEffectReplace : gdEffectNormal);
	switch(op.type) {
		case gds_DrawingOpType::Dot:
			image->SetPixel(op.Dot.x, op.Dot.y, op.Common.lineColour);
			break;

		case gds_DrawingOpType::Line:
			//Workaround for hang in libgd.
			if(op.Line.x1 > op.Line.x2){
				swap(op.Line.x1, op.Line.x2);
				swap(op.Line.y1, op.Line.y2);
			}
			/*if(p.Line.x1 == op.Line.x2){
				FastBox(*image, op.Line.x1, op.Line.y1, op.Common.lineWidth, max(op.Line.y1, op.Line.y2) - min(op.Line.y1, op.Line.y2), op.Common.lineColour);
			}else if(op.Line.y1 == op.Line.y2){
				FastBox(*image, op.Line.x1, op.Line.y1, max(op.Line.x1, op.Line.x2) - min(op.Line.x1, op.Line.x2), op.Common.lineWidth, op.Common.lineColour);
			}else{*/
				image->Line(op.Line.x1, op.Line.y1, op.Line.x2, op.Line.y2, op.Common.lineColour);
			//}
			break;

		case gds_DrawingOpType::Box:
			if(op.Common.fillStyle > 0) {
				if(image->Alpha(op.Common.fillColour)){
					image->FilledRectangle(op.Box.x, op.Box.y, op.Box.x + op.Box.w - 1, op.Box.y + op.Box.h - 1, op.Common.fillColour);
				}else{
					FastBox(*image, op.Box.x, op.Box.y, op.Box.w, op.Box.h, op.Common.fillColour);
				}
			}
			if(op.Common.lineWidth > 0){ 
				image->Rectangle(op.Box.x, op.Box.y, op.Box.x + op.Box.w - 1, op.Box.y + op.Box.h - 1, op.Common.lineColour);
			}
			break;

		case gds_DrawingOpType::Ellipse:
			if(op.Common.fillStyle > 0) {
				image->FilledEllipse(op.Ellipse.x, op.Ellipse.y, op.Ellipse.w, op.Ellipse.h, op.Common.fillColour);
			}
			if(op.Common.lineWidth > 0){ 
				image->Ellipse(op.Ellipse.x, op.Ellipse.y, op.Ellipse.w, op.Ellipse.h, op.Common.lineColour);
			}
			break;

		case gds_DrawingOpType::Arc:
			if(op.Common.fillStyle > 0) {
				image->FilledArc(op.Arc.x, op.Arc.y, op.Arc.w, op.Arc.h, op.Arc.a1, op.Arc.a2, op.Common.fillColour, 0);
			}
			if(op.Common.lineWidth > 0){ 
				image->Arc(op.Arc.x, op.Arc.y, op.Arc.w, op.Arc.h, op.Arc.a1, op.Arc.a2, op.Common.lineColour);
			}
			break;

		case gds_DrawingOpType::Blit: {
				auto srcSurface = allSurfaces[op.Blit.src].lock();
				if(srcSurface) {
					if(op.Blit.srcW == op.Blit.dstW && op.Blit.srcH == op.Blit.dstH){
						//FastBlit(*srcImage, *image, op.Blit.srcX, op.Blit.srcY, op.Blit.dstX, op.Blit.dstY, op.Blit.dstW, op.Blit.dstH);
						srcSurface->RenderTo(image, op.Blit.srcX, op.Blit.srcY, op.Blit.dstX, op.Blit.dstY, op.Blit.dstW, op.Blit.dstH, op.Blit.flags);
					}else{
						auto srcImage = srcSurface->Render(op.Blit.scale);
						if(srcImage){
							image->CopyResized(srcImage->GetPtr(), op.Blit.dstX, op.Blit.dstY, op.Blit.srcX, op.Blit.srcY, op.Blit.dstW, op.Blit.dstH, op.Blit.srcW, op.Blit.srcH);
						}
					}
				}
			}
			break;
		case gds_DrawingOpType::TextChar:{
				gdFTStringExtra ftex;
				ftex.flags = gdFTEX_RESOLUTION;
				ftex.vdpi = 72;
				ftex.hdpi = 72;
				string fontfile = GetFontManager()->GetFontFile(op.TextChar.fontID);
				char chstr[] = {op.TextChar.c, 0};
				if(fontfile != "" && op.TextChar.size) image->StringFT(NULL, op.Common.lineColour, (char*)fontfile.c_str(), op.TextChar.size, 0, op.TextChar.x, op.TextChar.y, chstr, &ftex);
			}
			break;
		case gds_DrawingOpType::Text:
		case gds_DrawingOpType::Polygon:
			pending_op = op;
			break;


		default:
			DBG("GDS: Unknown primitive " << op.type << " on surface " << this << "!");
			break;

	}
	//uint64_t op_end = bt_rtc_millis();
	//DBG("GDS: Operation " << op.type << " took " << (op_end - op_start) << "ms");
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

uint32_t BitmapSurface::GetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	return (uint32_t) image->ColorResolve(r, g, b, a);
}

std::shared_ptr<GD::Image> BitmapSurface::Render(uint32_t scale) {
	if(scale == this->scale) return image;
	else return std::shared_ptr<GD::Image>();
}

void BitmapSurface::SetOpParameters(std::shared_ptr<gds_OpParameters> params){
	if(pending_op.type != gds_DrawingOpType::None && pending_op.type == params->type){
		switch(pending_op.type){
			case gds_DrawingOpType::Text:{
					image->AlphaBlending((pending_op.Common.lineStyle & gds_TextStyle::PixelOverwrite) ? gdEffectReplace : gdEffectNormal);
					gdFTStringExtra ftex;
					ftex.flags = gdFTEX_RESOLUTION;
					ftex.vdpi = 72;
					ftex.hdpi = 72;
					string fontfile = GetFontManager()->GetFontFile(pending_op.Text.fontID);
					if(fontfile != "" && pending_op.Text.size) image->StringFT(NULL, pending_op.Common.lineColour, (char*)fontfile.c_str(), pending_op.Text.size, 0, pending_op.Text.x, pending_op.Text.y, params->data, &ftex);
				}
				break;
			case gds_DrawingOpType::Polygon:
				{
					size_t pointCount = params->size / sizeof(gds_Point);
					gdPoint points[pointCount];
					for(size_t i =0; i<pointCount; ++i){
						points[i].x = ((gds_Point*)params->data)[i].x;
						points[i].y = ((gds_Point*)params->data)[i].y;
						
					}
					if(pending_op.Common.fillStyle == gds_FillStyle::Filled) image->FilledPolygon(points, pointCount, pending_op.Common.fillColour);
					if(pending_op.Common.lineWidth > 0){ 
						if(pending_op.Polygon.closed) image->Polygon(points, pointCount, pending_op.Common.lineColour);
						else image->OpenPolygon(points, pointCount, pending_op.Common.lineColour);
					}
				}
				break;
			default:
				break;
		}
		pending_op.type = gds_DrawingOpType::None;
	}
}

std::shared_ptr<gds_OpParameters> BitmapSurface::GetOpParameters(uint32_t){
	auto ret = make_shared<gds_OpParameters>();
	ret->op_id = 0;
	ret->size = 0;
	return ret;
}

void BitmapSurface::ReorderOp(uint32_t /*op*/, uint32_t /*ref*/, gds_ReorderMode::Enum /*mode*/){
}

void BitmapSurface::Clear(){
	FastBox(*image, 0, 0, image->Width(), image->Height(), 0);
}

std::unique_ptr<gds_TextMeasurements> BitmapSurface::MeasureText(const gds_TextParameters &p, std::string text){
	return ::MeasureText(p, text);
}

void BitmapSurface::RenderTo(std::shared_ptr<GD::Image> dst, int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY, uint32_t w, uint32_t h, uint32_t flags){
	FastBlit(*image, *dst, srcX, srcY, dstX, dstY, w, h, flags);
}

std::shared_ptr<GD::Image> BitmapSurface::GetImage(){
	return image;
}

BitmapSurface::~BitmapSurface() {
}
