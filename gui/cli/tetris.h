#ifndef TETRIS_H_GUI
#define TETRIS_H_GUI
#include "../../brick_game/tetris/tetris.h"
#include "main.h"
#include "ncursesw/curses.h"
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

void tetrisGame();
void drawBorders();
void redrawField();
void decodeRedraw(int ch);
#ifdef __cplusplus
}
#endif
#endif