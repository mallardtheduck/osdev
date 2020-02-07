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
using namespace btos_api;
using namespace gds;
using namespace wm;

std::shared_ptr<Ball> ball;
std::shared_ptr<Paddle> paddle;
vector<shared_ptr<Sprite>> sprites;
queue<Rect> drawQ;
bool redrawScreen = false;
uint32_t curblocks = 0;
Font font;

void DrawBackground(shared_ptr<Surface> s){
	Colour col = s->GetColour(0, 0, 255);
	s->Box({0, 0, 320, 240}, col, col, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
}

void AddSprite(Sprite *s){
	shared_ptr<Sprite> sptr(s);
	sprites.push_back(sptr);
}

void RemoveSprite(shared_ptr<Sprite> s){
	drawQ.push(s->GetBoundingRect());
	sprites.erase(find(sprites.begin(), sprites.end(), s));
}

void DrawTitle(shared_ptr<Surface> s){
	Colour red = s->GetColour(255, 127, 127);
	s->Text({80, 30}, "Breakout!", font, 24, red);
	Colour green = s->GetColour(127, 255, 127);
	s->Text({60, 50}, "Press any key to start.", font, 16, green);
	s->Text({15, 210}, "Controls:", font, 12, green);
	s->Text({15, 225}, "Left/Right to move, Space to launch ball", font, 12, green);
}

void DrawEndScreen(shared_ptr<Surface> s){
	Colour red = s->GetColour(255, 127, 127);
	s->Text({110, 40}, "You win!", font, 24, red);
}

void InitBlocks(shared_ptr<Surface> s){
	vector<Colour> colours = {s->GetColour(255, 0, 255), s->GetColour(0, 255, 255), s->GetColour(255, 255, 0)};
	size_t ncolours = colours.size();
	size_t colidx = 0;
	for(size_t y = 0; y < 100; y+=Block::height){
		for(size_t x = 0; x < 320; x+=Block::width){
			AddSprite(new Block(s, {(int32_t)x, (int32_t)y}, colours[colidx]));
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

bool GameStep(shared_ptr<Surface> /*surf*/){
	vector<shared_ptr<Sprite>> currentSprites(sprites);
	for(auto s : currentSprites){
		auto preRect = s->GetBoundingRect();
		if(s->Step()){
			auto postRect = s->GetBoundingRect();
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

void GameDraw(shared_ptr<Window> win, shared_ptr<Surface> surf){
	sort(begin(sprites), end(sprites), &ZOrderSort);
	surf->BeginQueue();
	DrawBackground(surf);
	for(auto s : sprites){
		s->Draw();
	}
	surf->CommitQueue();
	if(!redrawScreen){
		if(!drawQ.empty()){
			auto rect = drawQ.front();
			drawQ.pop();
			while(!drawQ.empty()){
				auto rectl = rect.x + rect.w;
				auto rectb = rect.y + rect.h;
				auto &cur = drawQ.front();
				auto curl = cur.x + cur.w;
				auto curb = cur.y + cur.h;
				rect.x = min(rect.x, cur.x);
				rect.y = min(rect.y, cur.y);
				rectl = max(rectl, curl);
				rectb = max(rectb, curb);
				rect.w = rectl - rect.x;
				rect.h = rectb - rect.y;
				drawQ.pop();
			}
			win->Update(rect);
		}
		/*while(!drawQ.empty()){
			win->Update(drawQ.front());
			drawQ.pop();
		}*/
		WM_Sync();
	}else{
		win->Update();
		redrawScreen = false;
	}
}

void InitGame(shared_ptr<Surface> s, shared_ptr<Window> win){
	DrawBackground(s);
	ball.reset(new Ball(s));
	sprites.push_back(ball);
	paddle.reset(new Paddle(s));
	sprites.push_back(paddle);
	InitBlocks(s);
	redrawScreen = true;
	GameDraw(win, s);
}

void EndGame(){
	sprites = {};
	ball.reset();
	paddle.reset();
}
