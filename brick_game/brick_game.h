#ifndef BRICK_GAME_H
#define BRICK_GAME_H


#ifdef __cplusplus
extern "C" {
#endif
extern const char* tetrisRecordPath;
extern const char* snakeRecordPath;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  int end;
} GameInfo_t;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  Timer
} UserAction_t;

#ifdef __cplusplus
}
#endif

#endif