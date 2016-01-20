#include <gds/libgds.h>
#include <wm/libwm.h>
#include <memory>
#include <queue>
#include <algorithm>
#include "game.hpp"
#include "ball.hpp"
#include "block.hpp"
#include "paddle.hpp"
#include "sprite.hpp"

using namespace std;

std::shared_ptr<Ball> ball;
std::shared_ptr<Paddle> paddle;
vector<shared_ptr<Sprite>> sprites;
queue<wm_Rect> drawQ;
bool redrawScreen = false;
uint32_t curblocks = 0;

bool operator==(const wm_Rect &a, const wm_Rect &b){
	return (a.x == b.x) && (a.y == b.y) && (a.w == b.w) && (a.h == b.h);
}

bool operator!=(const wm_Rect &a, const wm_Rect &b){
	return !(a == b);
}

bool Overlaps(const wm_Rect &r1, const wm_Rect &r2){
	return !(r1.x + (int32_t)r1.w - 1 < r2.x || r1.y + (int32_t)r1.h - 1 < r2.y || r1.x > r2.x + (int32_t)r2.w - 1 || r1.y > r2.y + (int32_t)r2.h - 1);
}

void DrawBackground(){
	uint32_t col = GDS_GetColour(0, 0, 255);
	GDS_Box(0, 0, 320, 240, col, col, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
}

void AddSprite(Sprite *s){
	shared_ptr<Sprite> sptr(s);
	sprites.push_back(sptr);
}

void RemoveSprite(shared_ptr<Sprite> s){
	drawQ.push(s->GetBoundingRect());
	sprites.erase(find(sprites.begin(), sprites.end(), s));
}

void DrawTitle(){
	uint32_t red = GDS_GetColour(255, 127, 127);
	GDS_Text(100, 20, "Breakout!", gds_TEMPFonts::Giant, 0, red);
	uint32_t green = GDS_GetColour(127, 255, 127);
	GDS_Text(65, 40, "Press any key to start.", gds_TEMPFonts::Large, 0, green);
	GDS_Text(15, 200, "Controls:", gds_TEMPFonts::MediumBold, 0, green);
	GDS_Text(15, 215, "Left/Right to move, Space to launch ball", gds_TEMPFonts::MediumBold, 0, green);
}

void DrawEndScreen(){
	uint32_t red = GDS_GetColour(255, 127, 127);
	GDS_Text(110, 40, "You win!", gds_TEMPFonts::Giant, 0, red);
}

void InitBlocks(){
	uint32_t colours[] = {GDS_GetColour(255, 0, 255), GDS_GetColour(0, 255, 255), GDS_GetColour(255, 255, 0)};
	size_t ncolours = sizeof(colours) / sizeof(uint32_t);
	size_t colidx = 0;
	for(size_t y = 0; y < 100; y+=Block::height){
		for(size_t x = 0; x < 320; x+=Block::width){
			AddSprite(new Block(x, y, colours[colidx]));
			++curblocks;
			++colidx;
			if(colidx == ncolours) colidx = 0;
		}
	}
}

void RemoveBlock(){
	--curblocks;
}

void GameEvent(const wm_Event &e){
	for(auto s : sprites){
		s->Input(e);
	}
}

bool GameStep(){
	DrawBackground();
	vector<shared_ptr<Sprite>> currentSprites(sprites);
	for(auto s : currentSprites){
		wm_Rect preRect = s->GetBoundingRect();
		if(s->Step()){
			wm_Rect postRect = s->GetBoundingRect();
			if(preRect != postRect) drawQ.push(preRect);
			drawQ.push(postRect);
		}
	}
	if(curblocks == 0) return true;
	else return false;
}

bool ZOrderSort(shared_ptr<Sprite> a, shared_ptr<Sprite> b){
	if(!a) return true;
	if(!b) return false;
	return a->GetZOrder() < b->GetZOrder();
}

void GameDraw(){
	sort(begin(sprites), end(sprites), &ZOrderSort);
	for(auto s : sprites){
		s->Draw();
	}
	if(!redrawScreen){
		while(!drawQ.empty()){
			WM_UpdateRect(drawQ.front());
			drawQ.pop();
		}
		WM_Sync();
	}else{
		WM_Update();
		redrawScreen = false;
	}
}

void InitGame(){
	DrawBackground();
	ball.reset(new Ball());
	sprites.push_back(ball);
	paddle.reset(new Paddle());
	sprites.push_back(paddle);
	InitBlocks();
	redrawScreen = true;
	GameDraw();
}

void EndGame(){
	sprites = {};
	ball.reset();
	paddle.reset();
}