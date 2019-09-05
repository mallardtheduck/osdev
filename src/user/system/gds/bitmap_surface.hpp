#ifndef _BITMAP_SURFACE_HPP
#define _BITMAP_SURFACE_HPP

#include "gds.hpp"
#include "surface.hpp"
#include "drawingop.hpp"

class CompressedImageCursor{
private:
	const std::vector<std::pair<uint32_t, size_t>> *s;
	std::pair<uint32_t, size_t> cur;
	size_t idx = 0;
	size_t pos = 0;
	size_t w, h;
	size_t max;
	size_t size;
	
public:
	CompressedImageCursor() = default;
	
	CompressedImageCursor(const std::vector<std::pair<uint32_t, size_t>> &src, size_t width, size_t height) : 
	s(&src), w(width), h(height), max(w * h), size(s->size()){
		cur = (*s)[idx];
		++idx;
	}
	
	void GoTo(size_t x, size_t y){
		size_t target = (y * w) + x;
		if(target > max) return;
		
		if(pos > target){
			pos = 0;
			cur = s->front();
			idx = 1;
		}
		
		while(pos < target && idx < size){
			auto diff = target - pos;
			if(diff > cur.second){
				pos += cur.second;
				cur.second = 0;
			}else{
				cur.second -= diff;
				pos = target;
			}
			if(cur.second == 0){
				cur = (*s)[idx];
				++idx;
			}
		}
	}
	
	void Next(){
		if(pos >= max || idx > size) return;
		++pos;
		--cur.second;
		if(cur.second == 0){
			cur = (*s)[idx];
			++idx;
		}
	}
	
	uint32_t Read(){
		return cur.first;
	}
	
	size_t GetW(){
		return w;
	}
	
	size_t GetH(){
		return h;
	}
};

class BitmapSurface : public Surface{
protected:
	std::shared_ptr<GD::Image> image;
	std::vector<std::pair<uint32_t, size_t>> compressedImage;
	CompressedImageCursor cursor;
	
	bool isCompressed = false;
	
	uint32_t scale;
	gds_DrawingOp pending_op;
	uint32_t colourType;
	
	size_t width, height;

public:
	BitmapSurface(size_t w, size_t h, uint32_t colourType, uint32_t scale = 100);

	virtual size_t AddOperation(gds_DrawingOp op);
	virtual void RemoveOperation(size_t id);
	virtual gds_DrawingOp GetOperation(size_t id);
	virtual size_t GetWidth();
	virtual size_t GetHeight();
	virtual size_t GetDepth();
	virtual uint32_t GetScale();
	virtual void SetScale(uint32_t scale);
	virtual gds_SurfaceType::Enum GetType(); 
	virtual uint32_t GetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	virtual std::shared_ptr<GD::Image> Render(uint32_t scale);
	virtual void RenderTo(std::shared_ptr<GD::Image> dst, int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY, uint32_t w, uint32_t h, uint32_t flags);
	virtual void SetOpParameters(std::shared_ptr<gds_OpParameters>);
	virtual std::shared_ptr<gds_OpParameters> GetOpParameters(uint32_t op);
	virtual void ReorderOp(uint32_t op, uint32_t ref, gds_ReorderMode::Enum mode);
	virtual void Clear();
	virtual std::unique_ptr<gds_TextMeasurements> MeasureText(const gds_TextParameters &p, std::string text);
	
	virtual void Resize(size_t w, size_t h, bool indexed);
	
	virtual void Compress();
	void Decompress();
	
	std::shared_ptr<GD::Image> GetImage();

	virtual ~BitmapSurface();

public:

};

#endif //_BITMAP_SURFACE_HPP
