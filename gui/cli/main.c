#include "main.h"
const char *tetrisRecordPath = "";
const char *snakeRecordPath = "";
int main(int argc, char* argv[]) {
  if (argc > 1)
  {
    tetrisRecordPath = argv[1];
    snakeRecordPath = argv[2]; 
  } else {
    tetrisRecordPath = "brick_game/tetris/record.txt";
    snakeRecordPath = "brick_game/snake/record.txt";
  }
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  halfdelay(1);
  resizeterm(100, 100);
  start_color();
  init_pair(BORDER, COLOR_RED, COLOR_CYAN);
  init_pair(EMPTY, COLOR_BLUE, COLOR_BLACK);
  init_pair(TEXT, COLOR_CYAN, COLOR_BLACK);
  init_pair(TEXT_FOCUS, COLOR_BLACK, COLOR_CYAN);

  int game = mainMenu();
  clear();
  switch (game) {
  case 1:
    tetrisGame();
    break;

  case 2:
    snakeGame();
  }
  return 0;
}

int mainMenu() {
  int num = 1;
  while (1) {

    move(3, 6);
    attron(COLOR_PAIR(EMPTY));
    printw("WELCOME TO TETRIS 9999!");
    move(4, 6);
    printw("PLEASE, CHOOSE THE GAME:");

    const char *games[2] = {"TETRIS", "SNAKE"};
    for (int i = 1; i <= 2; i++) {
      if (i == num)
        attron(COLOR_PAIR(TEXT_FOCUS));
      else
        attron(COLOR_PAIR(TEXT));
      move(5 + i, 6);
      printw(games[i - 1]);
    }

    refresh();
    int ch = getch();
    switch (ch) {
    case 10:
      return num;
      break;
    case KEY_UP:
      num--;
      break;
    case KEY_DOWN:
      num++;
      break;
    }
    if (num < 1)
      num = 1;
    if (num > 2)
      num = 2;
  }
}

void drawBorders() {
  int y, x;
  move(3, 7);
  getyx(stdscr, y, x);

  attron(COLOR_PAIR(BORDER));
  hline(' ', 22);
  // основное поле
  for (int i = 1; i < 21; i++) {
    mvaddstr(y + i, x, " ");
    mvaddstr(y + i, x + 21, " ");
  }

  move(y, x + 22);
  getyx(stdscr, y, x);
  // три боковых поля
  for (int n = 0; n < 3; n++) {
    hline(' ', 13);

    for (int i = 1; i < 5; i++) {
      mvaddstr(y + i, x + 12, " ");
    }
    move(y + 5, x);
    getyx(stdscr, y, x);
  }
  // поле следующей фигуры
  hline(' ', 13);
  move(y + 1, x);
  getyx(stdscr, y, x);
  hline(' ', 13);

  for (int i = 1; i < 5; i++) {
    mvaddstr(y + i, x + 12, " ");
  }
  move(y + 5, x - 22);
  getyx(stdscr, y, x);
  // нижняя граница
  hline(' ', 35);
  attroff(COLOR_PAIR(BORDER));

  attron(COLOR_PAIR(EMPTY));
  move(4, 30);
  printw(" MAX SCORE");
  move(9, 30);
  printw(" SCORE");
  move(14, 30);
  printw(" LEVEL");
  attroff(COLOR_PAIR(EMPTY));
}
