#include "snake.hpp"

void startNewGameSnake() { newGameData(); }

void finishGameSnake()
{
  clearGameData();
  setHScoreToFile();
}

GameInfo_t getStateSnake() { return getStateSnakeModel(); }

void pushBtnSnake(int btn)
{
  switch (btn)
  {
  case Timer:
    moveSnake();
    break;
  case 'p':
    togglePause();
    break;
  case 10:
    actionPush();
    break;
  case 258 ... 261:
    turnSnake(btn);
    break;
  }
}
