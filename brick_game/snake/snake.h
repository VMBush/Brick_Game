#ifndef SNAKE_H
#define SNAKE_H
#include "../brick_game.h"

// Controller
void startNewGameSnake();
void finishGameSnake();
GameInfo_t getStateSnake();
void pushBtnSnake(int btn);

#endif