#include "snake.h"

void snakeGame() {
  init_pair(1, COLOR_RED, COLOR_GREEN);
  init_pair(2, COLOR_RED, COLOR_RED);

  drawBorders();
  startNewGameSnake();

  int ch;
  struct timespec start_time, current_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);
  timeout(1);
  while ((ch = getch()) != 'q') {
    GameInfo_t info = getStateSnake();
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    int delta = current_time.tv_sec * 1000 + current_time.tv_nsec / 1000000 -
                start_time.tv_sec * 1000 - start_time.tv_nsec / 1000000;
    if (delta >= 550 - 40 * info.level ||
        (ch == ' ' && delta >= 150 && info.level < 7)) {
      start_time = current_time;
      pushBtnSnake(Timer);
      redrawFieldSnake();
      refresh();
    }
    pushBtnSnake(ch);
  }
  finishGameSnake();
  endwin();
}

void redrawFieldSnake() {
  GameInfo_t field = getStateSnake();
  move(1, 6);
  attron(COLOR_PAIR(EMPTY));
  hline(' ', 11);
  if (field.end) {
    attron(COLOR_PAIR(TEXT_FOCUS));
    mvaddstr(1, 6, "GAME OVER!");
  }

  int y, x;
  move(3, 6);
  getyx(stdscr, y, x);
  for (int i = 1; i < 21; i++) {
    for (int j = 1; j < 11; j++) {
      if (field.field[i][j] != 0) {
        attron(COLOR_PAIR(field.field[i][j]));
        mvaddstr(y + i, x + j * 2, "  ");
        attroff(COLOR_PAIR(field.field[i][j]));
        refresh();
      } else {
        attron(COLOR_PAIR(EMPTY));
        mvaddstr(y + i, x + j * 2, "  ");
        attroff(COLOR_PAIR(EMPTY));
      }
    }
  }

  attron(COLOR_PAIR(EMPTY));
  move(6, 30);
  hline(' ', 11);
  printw(" %d", field.high_score);
  move(11, 30);
  hline(' ', 11);
  printw(" %d", field.score);
  move(16, 30);
  hline(' ', 11);
  printw(" %d", field.level);
  attroff(COLOR_PAIR(EMPTY));

  move(0, 0);
}
