#include "tests.h"
#define CK_FORK no

START_TEST(test_1) {
  startNewGameTetris();
  GameInfo_t info = updateCurrentState();
  ck_assert_int_eq(info.level, 1);

  info.end = 1;
  pushBtn(Start);
  pushBtn(Pause);
  info = updateCurrentState();
  ck_assert_int_eq(info.end, 0);
  ck_assert_int_eq(info.pause, 1);
  pushBtn(Pause);
  pushBtn(Timer);
  pushBtn(Timer);
  pushBtn(Left);
  pushBtn(Right);
  pushBtn(Up);
  pushBtn(Down);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      info.next[i][j] = 0;
    }
  }
  info.next[0][0] = 2;
  for (int i = 0; i < 3; i++) {
    info.next[1][i] = 2;
  }
  pushBtn(Action);
  pushBtn(Timer);
  pushBtn(Timer);
  pushBtn(Timer);
  for (int i = 0; i < 4; i++) {
    pushBtn(Up);
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      info.next[i][j] = 0;
    }
  }

  info.next[0][2] = 3;
  for (int i = 0; i < 3; i++) {
    info.next[1][i] = 3;
  }
  pushBtn(Action);
  pushBtn(Timer);
  pushBtn(Timer);
  pushBtn(Timer);
  for (int i = 0; i < 4; i++) {
    pushBtn(Up);
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      info.next[i][j] = 0;
    }
  }

  info.next[0][1] = 6;
  for (int i = 0; i < 3; i++) {
    info.next[1][i] = 6;
  }
  pushBtn(Action);
  pushBtn(Timer);
  pushBtn(Timer);
  pushBtn(Timer);
  for (int i = 0; i < 4; i++) {
    pushBtn(Up);
  }

  for (int i = 1; i < 11; i++) {
    info.field[20][i] = 1;
  }
  pushBtn(Action);
  finishGame();
}
END_TEST

Suite *make_tetris_suite(void) {
  Suite *s = suite_create("tetris");
  TCase *tc = tcase_create("case");

  tcase_add_test(tc, test_1);

  suite_add_tcase(s, tc);
  return s;
}
