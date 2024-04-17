#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <queue>




typedef enum
{
  LEFT,
  RIGHT,
  UP,
  DOWN
} Direction;

class Snake
{
public:
  std::queue<std::pair<int, int>> body;
  Direction curDir;
  Direction nextDir;
  std::pair<int, int> apple;
};


// Model
void newGameData();
void clearGameData();
void setHScoreToFile();
GameInfo_t getStateSnakeModel();
void generateApple();
void moveSnake();
void togglePause();
void actionPush();
void turnSnake(int cmd);

#endif