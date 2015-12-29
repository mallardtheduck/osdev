#include <gds/libgds.h>
#include <wm/libwm.h>

void DrawBackground(){
	uint32_t col = GDS_GetColour(0, 0, 255);
	GDS_Box(0, 0, 320, 240, col, col, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
}

void DrawTitle(){
	uint32_t red = GDS_GetColour(255, 127, 127);
	GDS_Text(100, 20, "Breakout!", gds_TEMPFonts::Giant, 0, red);
	uint32_t green = GDS_GetColour(127, 255, 127);
	GDS_Text(65, 40, "Press any key to start.", gds_TEMPFonts::Large, 0, green);	
}

void DrawBall(uint32_t x, uint32_t y){
	uint32_t green = GDS_GetColour(0, 255, 0);
	GDS_Ellipse(x, y, 10, 10, green, green, 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
}

enum class gamestate{
	Title,
	Game,
	Finish,
}

int main(){
    uint64_t surface = GDS_NewSurface(gds_SurfaceType::Bitmap, 320, 240);
	/*uint64_t win =*/ WM_NewWindow(100, 100, wm_WindowOptions::Default, wm_EventType::Keyboard | wm_EventType::Close, surface, "Breakout");
	DrawBackground();
	DrawTitle();
	WM_Update();
	gamestate state = gamestate::Title;
	while(true){
		wm_Event e = WM_GetEvent();
		if(e.type == wm_EventType::Close) break;
		switch(state){
			case gamestate::Title:{
				break;
			}
			case gamestate::Game:{
				break;
			}
			case gamestate::Finish:{
				break;
			}
		}
	}
    return 0;
}