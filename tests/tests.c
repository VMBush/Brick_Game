#include "tests.h"

int main() {
  Suite *s_tetris = make_tetris_suite();
  // Suite *s_remove = make_remove_suite();

  SRunner *runner = srunner_create(s_tetris);
  // srunner_add_suite(runner, s_remove);

  srunner_run_all(runner, CK_NORMAL);
  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
