#include "window.hpp"
#include <gds/libgds.h>

Window::Window(uint64_t surface_id) : gds_id(surface_id)
{
}

Window::~Window()
{
}

void Window::Draw(){
	GDS_SelectSurface(gds_id);
	gds_SurfaceInfo info = GDS_SurfaceInfo();
	GDS_SelectScreen();
	GDS_Box(x, y, info.w, 20, GDS_GetColour(0, 0, 0), GDS_GetColour(0, 0, 255), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	GDS_Blit(gds_id, 0, 0, info.w, info.h, x, y+20, info.w, info.h);
}