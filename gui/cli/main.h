#ifndef MAIN_H
#define MAIN_H
#include <ncurses/curses.h>
#include <stdio.h>
#include <string.h>
#include "../../brick_game/brick_game.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef enum {
  FIG_1 = 1,
  FIG_2,
  FIG_3,
  FIG_4,
  FIG_5,
  FIG_6,
  FIG_7,
  EMPTY,
  BORDER,
  TEXT,
  TEXT_FOCUS,
  SNAKE_BODY,
  APPLE
} myPairs;

int mainMenu();
void tetrisGame();
void snakeGame();
void drawBorders();

#ifdef __cplusplus
}
#endif
#endif