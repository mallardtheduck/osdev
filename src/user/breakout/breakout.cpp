#include <gds/libgds.h>
#include <wm/libwm.h>
#include <vector>
#include <dev/keyboard.h>

using namespace std;

void DrawBackground(){
	uint32_t col = GDS_GetColour(0, 0, 255);
	GDS_Box(0, 0, 320, 240, col, col, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
}

void DrawTitle(){
	uint32_t red = GDS_GetColour(255, 127, 127);
	GDS_Text(100, 20, "Breakout!", gds_TEMPFonts::Giant, 0, red);
	uint32_t green = GDS_GetColour(127, 255, 127);
	GDS_Text(65, 40, "Press any key to start.", gds_TEMPFonts::Large, 0, green);
	GDS_Text(15, 200, "Controls:", gds_TEMPFonts::MediumBold, 0, green);
	GDS_Text(15, 215, "Left/Right to move, Space to launch ball", gds_TEMPFonts::MediumBold, 0, green);
}

class Ball{
private:
	uint32_t x, y;
	int32_t xvel, yvel;
	uint32_t lx = 0, ly = 0;
	bool launched = false;
	
public:
	static const uint32_t size = 20;
	
	Ball(): x(170), y(120), xvel(0), yvel(0) {}
	
	void Launch(){
		if(!launched){
			xvel = 10;
			yvel = -10;
			launched = true;
		}
	}
	
	void Draw(){
		uint32_t green = GDS_GetColour(0, 255, 0);
		GDS_Ellipse(x, y, size, size, green, green, 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
		WM_UpdateRect(lx - size/2 - 1, ly - size/2 - 1, size + 2, size + 2);
		WM_UpdateRect(x - size/2 - 1, y - size/2 - 1, size + 2, size + 2);
	}
	
	void Step(){
		lx = x;
		ly = y;
		x += xvel;
		y += yvel;
	}
};

class Block{
private:
	uint32_t x, y;
	uint32_t colour;
	
public:
	static const uint32_t width = 40;
	static const uint32_t height = 20;

	Block(uint32_t sx, uint32_t sy, uint32_t col): x(sx), y(sy), colour(col) {}
	
	void Draw(){
		GDS_Box(x, y, width, height, colour, colour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		WM_UpdateRect(x, y, width, height);
	}
};

class Paddle{
private:
	uint32_t x = 145;
	uint32_t lx = 0;
	
public:
	static const uint32_t width = 50;
	static const uint32_t height = 20;
	static const uint32_t y = 200;
	static const uint32_t speed = 15;
	
	void Draw(){
		uint32_t colour = GDS_GetColour(128, 128, 128);
		GDS_Box(x, y, width, height, colour, colour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		WM_UpdateRect(lx, y, width, height);
		WM_UpdateRect(x, y, width, height);
	}
	
	void Left(){
		lx = x;
		x -= speed;
		if(x > lx) x = 0;
	}
	
	void Right(){
		lx = x;
		x += speed;
		if(x > 320 - width) x = 320 - width;
	}
};

enum class gamestate{
	Title,
	GameStart,
	GamePlay,
	Finish,
};

vector<Block> InitBlocks(){
	uint32_t colours[] = {GDS_GetColour(255, 0, 255), GDS_GetColour(0, 255, 255), GDS_GetColour(255, 255, 0)};
	size_t ncolours = sizeof(colours) / sizeof(uint32_t);
	size_t colidx = 0;
	vector<Block> blocks;
	for(size_t y = 0; y < 100; y+=Block::height){
		for(size_t x = 0; x < 320; x+=Block::width){
			blocks.push_back(Block(x, y, colours[colidx]));
			++colidx;
			if(colidx == ncolours) colidx = 0;
		}
	}
	return blocks;
}

int main(){
    uint64_t surface = GDS_NewSurface(gds_SurfaceType::Bitmap, 320, 240);
	/*uint64_t win =*/ WM_NewWindow(100, 100, wm_WindowOptions::Default, wm_EventType::Keyboard | wm_EventType::Close, surface, "Breakout");
	DrawBackground();
	DrawTitle();
	WM_Update();
	gamestate state = gamestate::Title;
	Ball ball;
	Paddle paddle;
	vector<Block> blocks;
	while(true){
		wm_Event e = WM_GetEvent();
		if(e.type == wm_EventType::Close) break;
		switch(state){
			case gamestate::Title:{
				if(e.type == wm_EventType::Keyboard) state = gamestate::GameStart;
				break;
			}
			case gamestate::GameStart:{
				DrawBackground();
				WM_Update();
				ball = Ball();
				ball.Draw();
				paddle = Paddle();
				paddle.Draw();
				blocks = InitBlocks();
				for(auto b : blocks){
					b.Draw();
				}
				state = gamestate::GamePlay;
				break;
			}
			case gamestate::GamePlay:{
				if(e.type == wm_EventType::Keyboard){
					uint16_t keycode = KB_code(e.Key.code);
					if(keycode == (KeyFlags::NonASCII | KeyCodes::LeftArrow)){
						paddle.Left();
					}else if(keycode == (KeyFlags::NonASCII | KeyCodes::RightArrow)){
						paddle.Right();
					}else if(KB_char(e.Key.code) == ' '){
						ball.Launch();
					}
				}
				ball.Step();
				DrawBackground();
				for(auto b : blocks){
					b.Draw();
				}
				ball.Draw();
				paddle.Draw();
				WM_Sync();
				break;
			}
			case gamestate::Finish:{
				break;
			}
		}
	}
    return 0;
}