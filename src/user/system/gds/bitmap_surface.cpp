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

static inline uint32_t murmur_32_scramble(uint32_t k) {
    k *= 0xcc9e2d51;
    k = (k << 15) | (k >> 17);
    k *= 0x1b873593;
    return k;
}

static uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed){
	uint32_t h = seed;
    uint32_t k;
    /* Read in groups of 4. */
    for (size_t i = len >> 2; i; i--) {
        // Here is a source of differing results across endiannesses.
        // A swap here has no effects on hash properties though.
        k = *((uint32_t*)key);
        key += sizeof(uint32_t);
        h ^= murmur_32_scramble(k);
        h = (h << 13) | (h >> 19);
        h = h * 5 + 0xe6546b64;
    }
    /* Read the rest. */
    k = 0;
    for (size_t i = len & 3; i; i--) {
        k <<= 8;
        k |= key[i - 1];
    }
    // A swap is *not* necessary here because the preceeding loop already
    // places the low bytes in the low places according to whatever endianess
    // we use. Swaps only apply when the memory is copied in a chunk.
    h ^= murmur_32_scramble(k);
    /* Finalize. */
	h ^= len;
	h ^= h >> 16;
	h *= 0x85ebca6b;
	h ^= h >> 13;
	h *= 0xc2b2ae35;
	h ^= h >> 16;
	return h;
}

static uint32_t HashImage(const CompressedImage &img){
	return murmur3_32(
		reinterpret_cast<const uint8_t*>(img.data()),
		img.size() * sizeof(img[0]),
		0x1234
	);
}

std::shared_ptr<CompressedImage> CompressedImageRegistry::AddImage(CompressedImage &&theImg){
	auto img = std::move(theImg);
	Refresh();
	uint32_t imghash = 0;
	for(auto &e : entries){
		auto eimage = e.image.lock();
		if(eimage && eimage->size() == img.size()){
			if(!e.hash)	e.hash = HashImage(*eimage);
			if(!imghash) imghash = HashImage(img);
			if(e.hash == imghash && std::equal(eimage->begin(), eimage->end(), img.begin())){
				//DBG("GDS: Image with hash " << imghash << " shared. " << (img.size() * sizeof(img[0])) << " bytes saved.");
				return eimage;
			}
		}
	}
	auto imgPtr = std::make_shared<CompressedImage>(std::move(img));
	Entry e;
	e.image = imgPtr;
	e.hash = imghash;
	entries.push_back(e);
	return imgPtr;
}

void CompressedImageRegistry::Refresh(){
	entries.erase(std::remove_if(entries.begin(), entries.end(), [](const Entry &e){
		return e.image.expired();
	}), entries.end());
}

CompressedImageRegistry &CompressedImageRegistry::Get(){
	static CompressedImageRegistry reg;
	return reg;
}

BitmapSurface::BitmapSurface(size_t w, size_t h, uint32_t cT, uint32_t scale)
: colourType(cT), width(w), height(h)
{
	bool indexed = !(cT & gds_ColourType::True);
	image.reset(new GD::Image((int)w, (int)h, !indexed));
	this->scale = scale;
	pending_op.type = gds_DrawingOpType::None;
}

size_t BitmapSurface::AddOperation(gds_DrawingOp op) {
	Decompress();
	//uint64_t op_start = bt_rtc_millis();
	image->SetThickness(op.Common.lineWidth);
	image->AlphaBlending(op.Common.fillStyle != gds_FillStyle::Overwrite);
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

std::vector<size_t> BitmapSurface::AddOperations(gds_MultiOps &mops){
	std::vector<size_t> ret {mops.count};
	for(size_t i = 0; i < mops.count; ++i) ret.push_back(AddOperation(mops.ops[i]));
	return ret;
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
	return width;
}

size_t BitmapSurface::GetHeight() {
	return height;
}

size_t BitmapSurface::GetDepth() {
	return colourType == gds_ColourType::True ? 32 : 8;
}

void BitmapSurface::Resize(size_t w, size_t h, bool indexed) {
	width = w; height = h;
	image.reset(new GD::Image((int)w, (int)h, !indexed));
	if(isCompressed){
		compressedImage.reset();
		CompressedImageRegistry::Get().Refresh();
		isCompressed = false;
	}
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
	Decompress();
	return (uint32_t) image->ColorResolve(r, g, b, a);
}

std::shared_ptr<GD::Image> BitmapSurface::Render(uint32_t scale) {
	Decompress();
	if(scale == this->scale) return image;
	else return std::shared_ptr<GD::Image>();
}

void BitmapSurface::SetOpParameters(std::shared_ptr<gds_OpParameters> params){
	Decompress();
	if(pending_op.type != gds_DrawingOpType::None && pending_op.type == params->type){
		switch(pending_op.type){
			case gds_DrawingOpType::Text:{
					image->AlphaBlending(!(pending_op.Common.lineStyle & gds_TextStyle::PixelOverwrite));
					gdFTStringExtra ftex;
					ftex.flags = gdFTEX_RESOLUTION | gdFTEX_FONTPATHNAME;
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
	if(isCompressed){
		image.reset(new GD::Image(width, height, true));
		compressedImage.reset();
		CompressedImageRegistry::Get().Refresh();
		isCompressed = false;
	}else FastBox(*image, 0, 0, image->Width(), image->Height(), 0);
}

std::unique_ptr<gds_TextMeasurements> BitmapSurface::MeasureText(const gds_TextParameters &p, std::string text){
	return ::MeasureText(p, text);
}

void BitmapSurface::RenderTo(std::shared_ptr<GD::Image> dst, int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY, uint32_t w, uint32_t h, uint32_t flags){
	if(isCompressed) FastBlitFromCompressed(cursor, *dst, srcX, srcY, dstX, dstY, w, h, flags);
	else FastBlit(*image, *dst, srcX, srcY, dstX, dstY, w, h, flags);
}

std::shared_ptr<GD::Image> BitmapSurface::GetImage(){
	return image;
}

void BitmapSurface::Compress(){
	if(isCompressed) return;
	if(!image->IsTrueColor()) return;
	
	size_t w = width, h = height;
	gdImagePtr ptr = image->GetPtr();
	
	CompressedImage cmpImg;
	cmpImg.reserve((w * h) / 2);
	
	std::pair<uint32_t, size_t> cur(0, 0);
	bool first = true;
	for(size_t y = 0; y < h; ++y){
		for(size_t x = 0; x < w; ++x){
			uint32_t col = gdImageTrueColorPixel(ptr, x, y);
			if(first){
				cur.first = col;
				first = false;
			}else{
				if(col != cur.first){
					cmpImg.push_back(cur);
					cur = {col, 0};
				}
			}
			++cur.second;
		}
	}
	cmpImg.push_back(cur);
	cmpImg.shrink_to_fit();
	
	int32_t saving = (image->Width() * image->Height() * 4) - (cmpImg.size() * 8);
	if(saving > 0){
		compressedImage = CompressedImageRegistry::Get().AddImage(std::move(cmpImg));
		cursor = {compressedImage, width, height};
		isCompressed = true;
		image.reset();
	}else{
		compressedImage.reset();
		isCompressed = false;
	}
}

void BitmapSurface::Decompress(){
	if(!isCompressed) return;
	btos_api::bt_zero("BitmapSurface::Decompress\n");
	
	size_t w = width, h = height;
	
	image.reset(new GD::Image(w, h, true));
	gdImagePtr ptr = image->GetPtr();
	
	size_t pos = 0;
	for(auto cur : *compressedImage){
		while(cur.second > 0){
			size_t y = pos / w;
			size_t x = pos % w;
			gdImageTrueColorPixel(ptr, x, y) = cur.first;
			--cur.second;
			++pos;
		}
	}
	
	isCompressed = false;
	compressedImage.reset();
	CompressedImageRegistry::Get().Refresh();
}

BitmapSurface::~BitmapSurface() {
}
