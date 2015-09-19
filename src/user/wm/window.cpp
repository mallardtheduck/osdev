#include <gds/libgds.h>
#include "window.hpp"
#include "metrics.hpp"
#include "drawing.hpp"

Window::Window(uint64_t surface_id) : x(0), y(0), gds_id(surface_id)
{
}

Window::~Window()
{
}

void Window::Draw(){
	GDS_SelectSurface(gds_id);
	gds_SurfaceInfo info = GDS_SurfaceInfo();
	GDS_SelectScreen();
	GDS_Blit(gds_id, 0, 0, info.w, info.h, x, y + GetMetric(TitleBarSize), info.w, info.h);
	DrawTitleBar(x, y, info.w);
	DrawBorder(x, y, info.w, info.h + GetMetric(TitleBarSize));
}

void Window::SetPosition(uint32_t nx, uint32_t ny){
	x=nx;
	y=ny;
}