#ifndef TETRIS_H
#define TETRIS_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../brick_game.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  int y;
  int x;
  int **fig;
} CurrentFig;

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();
void pushBtn(UserAction_t);
void pushTimer();
void scanField();
void moveFig(int dx);
void rotateFig(int way);
void rotateFig2(int way, int newf[4][4]);
void rotateFig3(int way, int newf[4][4]);
void rotateFig6(int way, int newf[4][4]);

void startNewGameTetris();
void finishGame();
void generateNext(int **newf);

int get_random_int(int min, int max);
int getFigType();
#ifdef __cplusplus
}
#endif


#endif
