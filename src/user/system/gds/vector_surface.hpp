#ifndef _VECTOR_SURFACE_HPP
#define _VECTOR_SURFACE_HPP

#include "gds.hpp"
#include "surface.hpp"
#include "drawingop.hpp"

class BitmapSurface;

class VectorSurface : public Surface{
private:
	struct VectorOp{
		size_t zOrder;
		gds_DrawingOp op;
		std::shared_ptr<gds_OpParameters> params;
	};
	std::map<uint32_t, VectorOp> ops;
	uint32_t opCounter = 0;
	uint32_t width;
	uint32_t height;
	uint32_t colourType;
	
	uint64_t cacheId = 0;
	
	bool update = false;
	
	struct Rectangle{
		int32_t x = 0, y = 0;
		uint32_t w = 0, h = 0;
		
		Rectangle() = default;
		Rectangle(int32_t _x, int32_t _y, uint32_t _w, uint32_t _h) : x(_x), y(_y), w(_w), h(_h) {}
	};
	
	friend bool operator==(const Rectangle &r1, const Rectangle &r2);
	friend bool operator!=(const Rectangle &r1, const Rectangle &r2);
	
	Rectangle renderRect, cacheRect;
	
	bool Contains(const Rectangle &outer, const Rectangle &inner);
	bool InRect(int32_t x, int32_t y, const Rectangle &r);
	bool Overlaps(const Rectangle &r1, const Rectangle &r2);
	
	bool OpInRect(const VectorOp &op, const Rectangle &rect);
	
	void OrderOps();
	
	std::shared_ptr<BitmapSurface> GetCache(bool &created);
	void DropCache();
	
	std::shared_ptr<BitmapSurface> RenderToCache();
public:
	VectorSurface(size_t w, size_t h, uint32_t colourType, uint32_t scale = 100);

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

	virtual ~VectorSurface();
};

#endif
