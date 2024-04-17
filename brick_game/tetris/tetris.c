#include "tetris.h"

static GameInfo_t gameStatus;
static CurrentFig currentFig;

void startNewGameTetris() {

  // игровое поле
  gameStatus.field = (int**)malloc(sizeof(int *) * 22);
  for (int i = 0; i < 22; i++) {
    gameStatus.field[i] = (int*)malloc(sizeof(int) * 12);
  }

  for (int i = 0; i < 12; i++) {
    gameStatus.field[0][i] = 99;
    gameStatus.field[21][i] = 99;
  }
  for (int i = 0; i < 22; i++) {
    gameStatus.field[i][0] = 99;
    gameStatus.field[i][11] = 99;
  }
  for (int i = 1; i < 21; i++) {
    for (int j = 1; j < 11; j++) {
      gameStatus.field[i][j] = 0;
    }
  }

  // следующая фигура
  gameStatus.next = (int**)malloc(sizeof(int *) * 4);
  for (int i = 0; i < 4; i++) {
    gameStatus.next[i] = (int*)malloc(sizeof(int) * 4);
  }
  generateNext(gameStatus.next);

  // положение фигуры
  currentFig.x = -1;
  currentFig.y = -1;
  currentFig.fig = (int**)malloc(sizeof(int *) * 4);
  for (int i = 0; i < 4; i++) {
    currentFig.fig[i] = (int*)malloc(sizeof(int) * 4);
  }

  // рекорд
  FILE *file = fopen(tetrisRecordPath, "r");
  fscanf(file, "%d", &(gameStatus.high_score));
  fclose(file);

  gameStatus.level = 1;
  gameStatus.pause = 0;
  gameStatus.score = 0;
  gameStatus.speed = 1;
  gameStatus.end = 1;
}

void finishGame() {
  for (int i = 0; i < 22; i++) {
    free(gameStatus.field[i]);
  }
  free(gameStatus.field);

  for (int i = 0; i < 4; i++) {
    free(gameStatus.next[i]);
  }
  free(gameStatus.next);

  for (int i = 0; i < 4; i++) {
    free(currentFig.fig[i]);
  }
  free(currentFig.fig);

  FILE *file = fopen(tetrisRecordPath, "w");
  fprintf(file, "%d", gameStatus.high_score);
  fclose(file);
}

int get_random_int(int min, int max) { return rand() % (max - min + 1) + min; }

void generateNext(int **newf) {

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      newf[i][j] = 0;
    }
  }

  int type = get_random_int(1, 7);
  switch (type) {
  case 1:
    for (int i = 0; i < 4; i++) {
      newf[0][i] = type;
    }
    break;

  case 2:
    newf[0][0] = type;
    for (int i = 0; i < 3; i++) {
      newf[1][i] = type;
    }
    break;

  case 3:
    newf[0][2] = type;
    for (int i = 0; i < 3; i++) {
      newf[1][i] = type;
    }
    break;

  case 4:
    for (int i = 1; i < 3; i++) {
      newf[0][i] = type;
      newf[1][i] = type;
    }
    break;

  case 5:
    for (int i = 0; i < 2; i++) {
      newf[0][i + 1] = type;
      newf[1][i] = type;
    }
    break;

  case 6:
    newf[0][1] = type;
    for (int i = 0; i < 3; i++) {
      newf[1][i] = type;
    }
    break;

  case 7:
    for (int i = 0; i < 2; i++) {
      newf[0][i] = type;
      newf[1][i + 1] = type;
    }
    break;
  }
}

GameInfo_t updateCurrentState() { return gameStatus; }

void pushBtn(UserAction_t btn) {
  if (gameStatus.end == 1) {

    if (btn == Start) {
      finishGame();
      startNewGameTetris();
      gameStatus.end = 0;
    }
  }

  else if (btn == Timer) {
    pushTimer();
  } else if (btn == Pause) {
    gameStatus.pause = 1 - gameStatus.pause;
  }

  else if (btn == Left) {
    moveFig(-1);
  } else if (btn == Right) {
    moveFig(1);
  } else if (btn == Up) {
    rotateFig(1);
  } else if (btn == Down) {
    rotateFig(-1);
  } else if (btn == Action) {
    while (currentFig.x != -1) {
      pushTimer();
    }
  }
}

void pushTimer() {
  if (currentFig.x == -1) {

    // ставим фигуру в начало
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {

        currentFig.fig[i][j] = gameStatus.next[i][j];

        if (currentFig.fig[i][j] != 0) {
          if (gameStatus.field[1 + i][4 + j] != 0) {
            gameStatus.end = 1;
            return;
          }
          gameStatus.field[1 + i][4 + j] = currentFig.fig[i][j];
        }
      }
    }
    generateNext(gameStatus.next);
    currentFig.x = 4;
    currentFig.y = 1;
  } else if (!gameStatus.pause) {
    // пробуем сместить фигуру вниз
    // если возможно- смещаем, если нет- останавливаем и даем знать, что нужна
    // следующая

    // если смещение невозможно
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (currentFig.fig[i][j] != 0 &&
            (i == 3 || currentFig.fig[i + 1][j] == 0)) {
          if (gameStatus.field[currentFig.y + i + 1][currentFig.x + j] != 0) {
            currentFig.x = -1;
            currentFig.y = -1;
            scanField();
            return;
          }
        }
      }
    }

    // если смещение возможно
    // очищаем старую фигуру
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (currentFig.fig[i][j] != 0) {
          gameStatus.field[currentFig.y + i][currentFig.x + j] = 0;
        }
      }
    }
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (currentFig.fig[i][j] != 0) {
          gameStatus.field[currentFig.y + i + 1][currentFig.x + j] =
              currentFig.fig[i][j];
        }
      }
    }
    currentFig.y++;
  }
}

void scanField() {
  int winCount = 0;
  for (int i = 1; i < 21; i++) { 
    bool winLine = 1;
    for (int j = 1; j < 11; j++) {
      if (gameStatus.field[i][j] == 0) {
        winLine = 0;
        break;
      }
    }

    if (winLine) {
      winCount++;
      for (int row = i; row > 1; row--) {
        for (int col = 1; col < 11; col++) {
          gameStatus.field[row][col] = gameStatus.field[row - 1][col];
        }
      }
      for (int col = 1; col < 11; col++) {
        gameStatus.field[1][col] = 0;
      }
    }
  }
  if (winCount == 1) {
    gameStatus.score += 100;
  } else if (winCount == 2) {
    gameStatus.score += 300;
  } else if (winCount == 3) {
    gameStatus.score += 700;
  } else if (winCount == 4) {
    gameStatus.score += 1500;
  }
  if (gameStatus.score > gameStatus.high_score) {
    gameStatus.high_score = gameStatus.score;
  }
  gameStatus.level = gameStatus.score / 600 + 1;
  if (gameStatus.level > 10)
    gameStatus.level = 10;
}

void moveFig(int dx) {
  if (currentFig.x == -1)
    return;
  bool possibility = 1;
  GameInfo_t info = updateCurrentState();

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      // если точка краевая
      if (currentFig.fig[i][j] != 0 &&
          (j + dx < 0 || j + dx > 3 || currentFig.fig[i][j + dx] == 0)) {
        // если сдвиг невозможен
        if (info.field[currentFig.y + i][currentFig.x + j + dx] != 0) {
          possibility = 0;
        }
      }
    }
  }

  if (possibility) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (currentFig.fig[i][j] != 0) {
          info.field[currentFig.y + i][currentFig.x + j] = 0;
        }
      }
    }
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (currentFig.fig[i][j] != 0) {
          info.field[currentFig.y + i][currentFig.x + j + dx] =
              currentFig.fig[i][j];
        }
      }
    }
    currentFig.x += dx;
  }
}

void rotateFig(int way) {
  GameInfo_t info = updateCurrentState();
  int type = getFigType();
  int newf[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      newf[i][j] = 0;
    }
  }
  switch (type) {
  case 1:
    if (currentFig.fig[0][0] == 1) {
      for (int i = 0; i < 4; i++) {
        newf[i][1] = 1;
      }
    } else {
      for (int i = 0; i < 4; i++) {
        newf[0][i] = 1;
      }
    }
    break;

  case 2:
    rotateFig2(way, newf);
    break;
  case 3:
    rotateFig3(way, newf);
    break;

  case 4:
    for (int i = 1; i < 3; i++) {
      newf[0][i] = type;
      newf[1][i] = type;
    }
    break;

  case 5:
    if (currentFig.fig[0][0] != 0) {
      for (int i = 0; i < 2; i++) {
        newf[0][i + 1] = type;
        newf[1][i] = type;
      }
    } else {
      for (int i = 0; i < 2; i++) {
        newf[i][0] = type;
        newf[i + 1][1] = type;
      }
    }
    break;

  case 6:
    rotateFig6(way, newf);
    break;

  case 7:
    if (currentFig.fig[0][0] == 0) {
      for (int i = 0; i < 2; i++) {
        newf[0][i] = type;
        newf[1][i + 1] = type;
      }
    } else {
      for (int i = 0; i < 2; i++) {
        newf[i + 1][0] = type;
        newf[i][1] = type;
      }
    }
    break;
  }

  // если поворот невозможен завершаемся
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (newf[i][j] != 0 && currentFig.fig[i][j] == 0 &&
          (currentFig.y + i > 20 || currentFig.x + j < 1 ||
           currentFig.x + j > 10 ||
           info.field[currentFig.y + i][currentFig.x + j] != 0)) {
        return;
      }
    }
  }
  // если поворот возможен, поворачиваем
  // чистим
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (currentFig.fig[i][j] != 0) {
        info.field[currentFig.y + i][currentFig.x + j] = 0;
      }
    }
  }
  // записываем
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      currentFig.fig[i][j] = newf[i][j];
      if (currentFig.fig[i][j] != 0) {
        info.field[currentFig.y + i][currentFig.x + j] = currentFig.fig[i][j];
      }
    }
  }
}

void rotateFig2(int way, int newf[4][4]) {
  int states[4][4][4];

  for (int n = 0; n < 4; n++) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        states[n][i][j] = 0;
      }
    }
  }

  states[0][0][0] = states[1][0][1] = states[2][1][2] = states[3][2][0] = 2;

  for (int i = 0; i < 3; i++) {
    states[0][1][i] = states[1][i][0] = states[2][0][i] = states[3][i][1] = 2;
  }

  int curState = -1;
  if (currentFig.fig[0][0] != 0 && currentFig.fig[0][1] == 0)
    curState = 0;
  else if (currentFig.fig[2][0] != 0 && currentFig.fig[1][0] != 0)
    curState = 1;
  else if (currentFig.fig[1][2] != 0 && currentFig.fig[1][1] == 0)
    curState = 2;
  else if (currentFig.fig[2][0] != 0 && currentFig.fig[1][0] == 0)
    curState = 3;

  int newState = (curState + way + 4) % 4;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      newf[i][j] = states[newState][i][j];
    }
  }
}

void rotateFig3(int way, int newf[4][4]) {
  int states[4][4][4];

  for (int n = 0; n < 4; n++) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        states[n][i][j] = 0;
      }
    }
  }

  states[0][0][2] = states[1][2][1] = states[2][1][0] = states[3][0][0] = 3;

  for (int i = 0; i < 3; i++) {
    states[0][1][i] = states[1][i][0] = states[2][0][i] = states[3][i][1] = 3;
  }

  int curState = -1;
  if (currentFig.fig[0][2] != 0 && currentFig.fig[0][1] == 0)
    curState = 0;
  else if (currentFig.fig[2][0] != 0 && currentFig.fig[1][0] != 0)
    curState = 1;
  else if (currentFig.fig[0][2] != 0 && currentFig.fig[0][1] != 0)
    curState = 2;
  else if (currentFig.fig[2][1] != 0 && currentFig.fig[1][1] != 0)
    curState = 3;

  int newState = (curState + way + 4) % 4;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      newf[i][j] = states[newState][i][j];
    }
  }
}

void rotateFig6(int way, int newf[4][4]) {
  int states[4][4][4];

  for (int n = 0; n < 4; n++) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        states[n][i][j] = 0;
      }
    }
  }

  states[0][0][1] = states[1][1][1] = states[2][1][1] = states[3][1][0] = 6;

  for (int i = 0; i < 3; i++) {
    states[0][1][i] = states[1][i][0] = states[2][0][i] = states[3][i][1] = 6;
  }

  int curState = -1;
  if (currentFig.fig[1][2] != 0)
    curState = 0;
  else if (currentFig.fig[2][0] != 0)
    curState = 1;
  else if (currentFig.fig[0][2] != 0)
    curState = 2;
  else if (currentFig.fig[2][1] != 0)
    curState = 3;

  int newState = (curState + way + 4) % 4;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      newf[i][j] = states[newState][i][j];
    }
  }
}

int getFigType() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (currentFig.fig[i][j] != 0) {
        return currentFig.fig[i][j];
      }
    }
  }
  return 0;
}
