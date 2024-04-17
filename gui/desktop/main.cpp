#include "mainwindow.h"

#include <QApplication>
#include <filesystem>
#include <iostream>
#include <string.h>

const char *tetrisRecordPath = "";
const char *snakeRecordPath = "";

int main(int argc, char *argv[])
{
    std::string abc = std::filesystem::current_path().u8string();
    std::cout << "Current path is " << std::filesystem::current_path().u8string() << '\n';
    if (argc > 1)
    {
        tetrisRecordPath = argv[1];
        snakeRecordPath = argv[2];
    } else {
        tetrisRecordPath = "../../brick_game/tetris/record.txt";
        snakeRecordPath = "../../brick_game/snake/record.txt";
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
