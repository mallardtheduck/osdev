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
extern btos_api::gds::Font font;

void DrawBackground(std::shared_ptr<btos_api::gds::Surface> s);
void DrawTitle(std::shared_ptr<btos_api::gds::Surface> s);
void DrawEndScreen(std::shared_ptr<btos_api::gds::Surface> s);

void InitGame(std::shared_ptr<btos_api::gds::Surface> s, std::shared_ptr<btos_api::wm::Window> win);
void EndGame();
void GameEvent(const wm_Event &e);
bool GameStep(std::shared_ptr<btos_api::gds::Surface> s);
void GameDraw(std::shared_ptr<btos_api::wm::Window> win, std::shared_ptr<btos_api::gds::Surface> s);

void AddSprite(Sprite *s);
void RemoveSprite(std::shared_ptr<Sprite> s);
void RemoveBlock();

#endif
