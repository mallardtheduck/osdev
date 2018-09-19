#ifndef _GAME_HPP
#define _GAME_HPP

#include <memory>
#include <wm/libwm.h>
#include <gds/surface.hpp>
#include <wm/window.hpp>
#include "ball.hpp"
#include "paddle.hpp"

extern std::shared_ptr<Ball> ball;
extern std::shared_ptr<Paddle> paddle;
extern gds::Font font;

bool Overlaps(const gds::Rect &r1, const gds::Rect &r2);

void DrawBackground(std::shared_ptr<gds::Surface> s);
void DrawTitle(std::shared_ptr<gds::Surface> s);
void DrawEndScreen(std::shared_ptr<gds::Surface> s);

void InitGame(std::shared_ptr<gds::Surface> s, std::shared_ptr<wm::Window> win);
void EndGame();
void GameEvent(const wm_Event &e);
bool GameStep(std::shared_ptr<gds::Surface> s);
void GameDraw(std::shared_ptr<wm::Window> win, std::shared_ptr<gds::Surface> s);

void AddSprite(Sprite *s);
void RemoveSprite(std::shared_ptr<Sprite> s);
void RemoveBlock();

#endif
