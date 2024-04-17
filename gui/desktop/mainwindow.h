#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include "../../brick_game/tetris/tetris.h"
#include "../../brick_game/snake/snake.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startTetris_clicked();

    void on_startSnake_clicked();

    void on_quit_clicked();

    void on_pause_clicked();

private:
    Ui::MainWindow *ui;
    QString activeGame;
    QGraphicsScene* field;
    QGraphicsScene* fieldAddition;
    void updateGameData();
    void playTetris();
    void playSnake();
    void endGame(QString name);
    void tetrisTick();
    void redrawTetris();

    void keyPressEvent(QKeyEvent *event) override;
    void keyPressEventTetris(int key);
    void keyPressEventSnake(int key);

    QTimer* timer;
};

QPixmap getTetrisImg(int type);
#endif // MAINWINDOW_H
