#include <vector>

#include "tests.h"

TEST(snake, start) {
  startNewGameSnake();
  GameInfo_t info = getStateSnake();
  ASSERT_EQ(info.end, 0);
  ASSERT_NE(info.field[0][0], 0);
  ASSERT_EQ(info.level, 1);
}

TEST(snake, finish)
{
  finishGameSnake();
  GameInfo_t info = getStateSnake();
  ASSERT_EQ(info.end, 0);
  ASSERT_EQ(info.field, nullptr);
  ASSERT_EQ(info.level, 1);
}

TEST(snake, beginGame)
{
  startNewGameSnake();
  pushBtnSnake(10);
  GameInfo_t info = getStateSnake();
  ASSERT_EQ(info.end, 0);
  ASSERT_EQ(info.pause, 0);
  ASSERT_EQ(info.level, 1);
}

TEST(snake, movingToDeath)
{
  for (int i = 0; i < 15; i++)
    pushBtnSnake(Timer);
  GameInfo_t info = getStateSnake();
  pushBtnSnake(10);
  ASSERT_EQ(info.end, 1);
  ASSERT_EQ(info.pause, 0);
  ASSERT_EQ(info.level, 1);
}

TEST(snake, turningToDeath)
{
  startNewGameSnake();
  pushBtnSnake(10);

  pushBtnSnake(Timer);
  pushBtnSnake(260);
  pushBtnSnake(259);
  pushBtnSnake(Timer);
  pushBtnSnake(258);
  pushBtnSnake(260);
  pushBtnSnake(Timer);
  pushBtnSnake(261);
  pushBtnSnake(258);
  pushBtnSnake(Timer);
  pushBtnSnake(259);
  pushBtnSnake(261);
  pushBtnSnake(Timer);

  GameInfo_t info = getStateSnake();
  ASSERT_EQ(info.end, 1);
  ASSERT_EQ(info.pause, 0);
  ASSERT_EQ(info.level, 1);
}

TEST(snake, pause)
{
  startNewGameSnake();
  pushBtnSnake(10);

  pushBtnSnake('p');
  GameInfo_t info = getStateSnake();
  ASSERT_EQ(info.pause, 1);
  pushBtnSnake('p');
  info = getStateSnake();
  ASSERT_EQ(info.pause, 0);

  pushBtnSnake(10);

}
