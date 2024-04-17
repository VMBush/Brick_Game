#ifndef SNAKE_H_GUI
#define SNAKE_H_GUI
#include "../../brick_game/snake/snake.h"
#include "main.h"
#include "ncursesw/curses.h"
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

void snakeGame();

void redrawFieldSnake();
#ifdef __cplusplus
}
#endif
#endif