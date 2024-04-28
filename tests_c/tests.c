#include "tests.h"

const char *tetrisRecordPath = "";
const char *snakeRecordPath = "";

int main() {
  tetrisRecordPath = "brick_game/tetris/record.txt";
  snakeRecordPath = "brick_game/snake/record.txt";

  Suite *s_tetris = make_tetris_suite();
  // Suite *s_remove = make_remove_suite();

  SRunner *runner = srunner_create(s_tetris);
  // srunner_add_suite(runner, s_remove);

  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
