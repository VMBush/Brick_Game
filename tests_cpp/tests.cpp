#include "tests.h"

const char *tetrisRecordPath = "";
const char *snakeRecordPath = "";

int main(int argc, char **argv) {
  tetrisRecordPath = "brick_game/tetris/record.txt";
  snakeRecordPath = "brick_game/snake/record.txt";

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}