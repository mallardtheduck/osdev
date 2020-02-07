#ifndef _SHM_SURFACE_HPP
#define _SHM_SURFACE_HPP

#include "gds.hpp"
#include "surface.hpp"
#include "drawingop.hpp"

class SHMSurface : public Surface{
private:
	btos_api::bt_handle_t shm_handle;
	uint32_t width;
	uint32_t height;
	uint32_t colourType;
	char *ptr;
	
	std::array<uint32_t, 256> palette;
public:
	SHMSurface(size_t w, size_t h, uint32_t colourType, uint32_t scale, uint64_t shmRegion, size_t shmOffset);

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

	virtual ~SHMSurface();
};

#endif
