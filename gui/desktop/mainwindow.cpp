#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), activeGame("")
{
    ui->setupUi(this);

    field = new QGraphicsScene;
    fieldAddition = new QGraphicsScene;
    ui->field->setScene(field);
    ui->fieldAdditional->setScene(fieldAddition);

    ui->gameOver->setVisible(false);

    actionPushed = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startTetris_clicked()
{
    if (activeGame != "") {
        endGame(activeGame);
    }
    activeGame = "Tetris";
    playTetris();
}


void MainWindow::on_startSnake_clicked()
{
    if (activeGame != "") {
        endGame(activeGame);
    }
    activeGame = "Snake";
    playSnake();
}

void MainWindow::endGame(QString name) {
    if (name == "Tetris") {
        finishGame();
    } else if (name == "Snake") {
        finishGameSnake();
    }
    if (timer) timer->stop();
    delete timer;
    timer = nullptr;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (activeGame == "Tetris") {
        keyPressEventTetris(event->key());
    }
    else if (activeGame == "Snake") {
        keyPressEventSnake(event->key());
    }

    if (event->key() == Qt::Key_Space && !event->isAutoRepeat()) {
        actionPushed = 1;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Space && !event->isAutoRepeat()) {
        actionPushed = 0;
    }
}

void MainWindow::on_quit_clicked()
{
    if (activeGame != "") endGame(activeGame);
    this->close();
}


void MainWindow::on_pause_clicked()
{
    QKeyEvent* press = new QKeyEvent(QEvent::KeyPress, Qt::Key_P, Qt::NoModifier);
    QApplication::sendEvent(this, press);
    delete press;
    press = new QKeyEvent(QEvent::KeyRelease, Qt::Key_P, Qt::NoModifier);
    QApplication::sendEvent(this, press);
    delete press;
}

