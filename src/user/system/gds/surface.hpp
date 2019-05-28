#ifndef _SURFACE_HPP
#define _SURFACE_HPP

#include "gds.hpp"
#include "drawingop.hpp"

class Surface {
public:
	uint64_t id;

	virtual size_t AddOperation(gds_DrawingOp op) = 0;
	virtual void RemoveOperation(size_t id) = 0;
	virtual gds_DrawingOp GetOperation(size_t id) = 0;
	virtual size_t GetWidth() = 0;
	virtual size_t GetHeight() = 0;
	virtual size_t GetDepth() = 0;
	virtual uint32_t GetScale() = 0;
	virtual void SetScale(uint32_t scale) = 0;
	virtual gds_SurfaceType::Enum GetType() = 0;
	virtual uint32_t GetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
	virtual std::shared_ptr<GD::Image> Render(uint32_t scale) = 0;
	virtual void RenderTo(std::shared_ptr<GD::Image> dst, int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY, uint32_t w, uint32_t h, uint32_t flags) = 0;
	virtual void SetOpParameters(std::shared_ptr<gds_OpParameters> params) = 0;
	virtual std::shared_ptr<gds_OpParameters> GetOpParameters(uint32_t op) = 0;
	virtual void ReorderOp(uint32_t op, uint32_t ref, gds_ReorderMode::Enum mode) = 0;
	virtual void Clear() = 0;
	virtual std::unique_ptr<gds_TextMeasurements> MeasureText(const gds_TextParameters &p, std::string text) = 0;
	
	virtual ~Surface() {};
};

#endif
