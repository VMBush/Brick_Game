#include "snake.hpp"

static GameInfo_t gameStatus;
static Snake snake;

void newGameData()
{
    srand((int)time(NULL) * 1234);
    //  игровое поле
    gameStatus.field = (int **)malloc(sizeof(int *) * 22);
    for (int i = 0; i < 22; i++)
    {
        gameStatus.field[i] = (int *)malloc(sizeof(int) * 12);
    }

    for (int i = 0; i < 12; i++)
    {
        gameStatus.field[0][i] = 99;
        gameStatus.field[21][i] = 99;
    }
    for (int i = 0; i < 22; i++)
    {
        gameStatus.field[i][0] = 99;
        gameStatus.field[i][11] = 99;
    }
    for (int i = 1; i < 21; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            gameStatus.field[i][j] = 0;
        }
    }
    while (!snake.body.empty())
    {
        snake.body.pop();
    }

    for (int i = 0; i < 4; i++)
    {
        gameStatus.field[10][i+2] = 1;
        snake.body.push({10, i+2});
    }

    snake.curDir = RIGHT;
    snake.nextDir = RIGHT;
    generateApple();

    // рекорд
    FILE *file = fopen(snakeRecordPath, "r");
    if (!file) gameStatus.high_score = 0;
    else {
        fscanf(file, "%d", &(gameStatus.high_score));
        fclose(file);
    }

    gameStatus.level = 1;
    gameStatus.pause = 1;
    gameStatus.score = 0;
    gameStatus.speed = 1;
    gameStatus.end = 0;
}

void clearGameData()
{
    for (int i = 0; i < 22; i++)
    {
        free(gameStatus.field[i]);
    }
    free(gameStatus.field);
    gameStatus.field = nullptr;
}

void setHScoreToFile()
{
    FILE *file = fopen(snakeRecordPath, "w");
    if (file) {
        fprintf(file, "%d", gameStatus.high_score);
        fclose(file);
    }
}

GameInfo_t getStateSnakeModel() { return gameStatus; }

void generateApple()
{
    int place = rand() % (200 - snake.body.size());
    int fieldIdx = 10;
    for (int i = 0; i < place; i++)
    {
        fieldIdx++;
        if (gameStatus.field[fieldIdx / 10][1 + fieldIdx % 10] != 0)
            i--;
    }
    snake.apple = {fieldIdx / 10, 1 + fieldIdx % 10};
    // snake.apple = {10, 6};
    gameStatus.field[fieldIdx / 10][1 + fieldIdx % 10] = 2;
    // gameStatus.field[10][6] = 2;
}

void moveSnake()
{
    if (gameStatus.end || gameStatus.pause) return;
    std::pair<int, int> headPos = snake.body.back();
    std::pair<int, int> headDest = headPos;
    switch (snake.nextDir)
    {
    case UP:
        headDest.first--;
        break;
    case DOWN:
        headDest.first++;
        break;
    case LEFT:
        headDest.second--;
        break;
    case RIGHT:
        headDest.second++;
        break;
    }
    snake.curDir = snake.nextDir;

    if (gameStatus.field[headDest.first][headDest.second] == 2) {
        // яблоко
        snake.body.push({headDest.first, headDest.second});
        gameStatus.field[headDest.first][headDest.second] = 1;
        generateApple();
        gameStatus.score++;
        if (gameStatus.score % 5 == 0) gameStatus.level++;
        if (gameStatus.level > 10) gameStatus.level = 10;
        if (gameStatus.score > gameStatus.high_score) gameStatus.high_score = gameStatus.score;
    }
    else if (gameStatus.field[headDest.first][headDest.second] != 0)
    {
        gameStatus.end = 1;
    }
    else {
        // движение
        snake.body.push({headDest.first, headDest.second});
        gameStatus.field[snake.body.front().first][snake.body.front().second] = 0;
        snake.body.pop();
        gameStatus.field[headDest.first][headDest.second] = 1;
    }
}

void togglePause() {
    gameStatus.pause = 1 - gameStatus.pause;
}

void actionPush() {
    if (gameStatus.end) {
        startNewGameSnake();
        togglePause();
    } else if (gameStatus.pause) {
        togglePause();
    }
}

void turnSnake(int cmd) {
    switch (cmd)
    {
    case 258:
        if (snake.curDir != UP) {
            snake.nextDir = DOWN;
        }
        break;

    case 259:
        if (snake.curDir != DOWN)
        {
            snake.nextDir = UP;
        }
        break;
    case 260:
        if (snake.curDir != RIGHT) {
            snake.nextDir = LEFT;
        }
        break;
    case 261:
        if (snake.curDir != LEFT)
        {
            snake.nextDir = RIGHT;
        }
        break;
    }
}
