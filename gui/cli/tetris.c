#include "tetris.h"

void tetrisGame() {
  init_pair(FIG_1, COLOR_RED, COLOR_BLUE);
  init_pair(FIG_2, COLOR_RED, COLOR_GREEN);
  init_pair(FIG_3, COLOR_RED, COLOR_MAGENTA);
  init_pair(FIG_4, COLOR_RED, COLOR_RED);
  init_pair(FIG_5, COLOR_RED, COLOR_WHITE);
  init_pair(FIG_6, COLOR_RED, COLOR_YELLOW);
  init_pair(FIG_7, COLOR_RED, COLOR_GREEN);

  drawBorders();
  startNewGameTetris();

  int ch;
  struct timespec start_time, current_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);
  timeout(1);
  while ((ch = getch()) != 'q') {
    GameInfo_t info = updateCurrentState();
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    if (current_time.tv_sec * 1000 + current_time.tv_nsec / 1000000 -
            start_time.tv_sec * 1000 - start_time.tv_nsec / 1000000 >=
        830 - 80 * info.level) {
      start_time = current_time;
      pushBtn(Timer);
      redrawField();
      refresh();
    }
    decodeRedraw(ch);
    refresh();
  }
  finishGame();
  endwin();
  
}

void redrawField() {
  GameInfo_t field = updateCurrentState();
  int y, x;
  move(3, 6);
  getyx(stdscr, y, x);
  for (int i = 1; i < 21; i++) {
    for (int j = 1; j < 11; j++) {
      if (field.field[i][j] != 0) {
        attron(COLOR_PAIR(field.field[i][j]));
        mvaddstr(y + i, x + j * 2, "  ");
        attroff(COLOR_PAIR(field.field[i][j]));
      } else {
        attron(COLOR_PAIR(EMPTY));
        mvaddstr(y + i, x + j * 2, "  ");
        attroff(COLOR_PAIR(EMPTY));
      }
    }
  }

  move(21, 32);
  getyx(stdscr, y, x);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      if (field.next[i][j] != 0) {
        attron(COLOR_PAIR(field.next[i][j]));
        mvaddstr(y + i, x + j * 2, "  ");
        attroff(COLOR_PAIR(field.next[i][j]));
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

void decodeRedraw(int ch) {
  switch (ch) {
  case KEY_UP:
    pushBtn(Up);
    redrawField();
    break;
  case KEY_DOWN:
    pushBtn(Down);
    redrawField();
    break;
  case KEY_LEFT:
    pushBtn(Left);
    redrawField();
    break;
  case KEY_RIGHT:
    pushBtn(Right);
    redrawField();
    break;
  case 10:
    pushBtn(Start);
    break;
  case 'p':
    pushBtn(Pause);
    break;
  case ' ':
    pushBtn(Action);
    redrawField();
    break;
  }
}