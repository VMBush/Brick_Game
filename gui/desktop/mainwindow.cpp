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
    startNewGameSnake();
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

void MainWindow::playTetris() {
    timer = new QTimer(this);
    timer->setInterval(830);
    QObject::connect(timer, &QTimer::timeout, this, tetrisTick);
    timer->start();

    startNewGameTetris();
    redrawTetris();
}

void MainWindow::tetrisTick() {
    setFocus();
    pushBtn(UserAction_t::Timer);
    redrawTetris();
}

void MainWindow::redrawTetris() {
    QGraphicsScene* newField = new QGraphicsScene;
    QGraphicsScene* newFieldAddition = new QGraphicsScene;
    newField->setSceneRect(0, 0, ui->field->width(), ui->field->height());

    GameInfo_t info = updateCurrentState();
    if (info.end == 1) ui->gameOver->setVisible(true);
    else ui->gameOver->setVisible(false);

    ui->hScore->display(info.high_score);
    ui->score->display(info.score);
    ui->level->display(info.level);

    int w = ui->field->width() / 10;
    int h = ui->field->height() / 20;
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= 10; j++) {
            if (info.field[i][j] == 0) continue;
            QPixmap pix = getTetrisImg(info.field[i][j]);

            QGraphicsPixmapItem* item = newField->addPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
            item->setPos((j-1)*(w), (i-1)*(h));
        }
    }

    for (int i = 0; i < 4 ; i++) {
        for (int j = 0; j < 4; j++) {
            if (info.next[i][j] == 0) continue;
            QPixmap pix = getTetrisImg(info.next[i][j]);
            QGraphicsPixmapItem* item = newFieldAddition->addPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
            item->setPos(j*w, i*h);
        }
    }

    delete field;
    field = newField;
    ui->field->setScene(field);

    delete fieldAddition;
    fieldAddition = newFieldAddition;
    ui->fieldAdditional->setScene(fieldAddition);

    info = updateCurrentState();
    timer->stop();
    timer->setInterval(830 - 60 * info.level);
    timer->start();
}

QPixmap getTetrisImg(int type) {
    QPixmap pix;
    switch (type) {
    case 1:
        pix = QPixmap(":/img/img/tetris/blue.png");
        break;
    case 2:
        pix = QPixmap(":/img/img/tetris/cyan.png");
        break;
    case 3:
        pix = QPixmap(":/img/img/tetris/green.png");
        break;
    case 4:
        pix = QPixmap(":/img/img/tetris/light-blue.png");
        break;
    case 5:
        pix = QPixmap(":/img/img/tetris/orange.png");
        break;
    case 6:
        pix = QPixmap(":/img/img/tetris/red.png");
        break;
    case 7:
        pix = QPixmap(":/img/img/tetris/yellow.png");
        break;

    default:
        break;
    }

    return pix;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (activeGame == "Tetris") {
        keyPressEventTetris(event->key());
    }
}

void MainWindow::keyPressEventTetris(int key) {
    switch(key) {
    case Qt::Key_Up:
        pushBtn(Up);
        redrawTetris();
        break;
    case Qt::Key_Down:
        pushBtn(Down);
        redrawTetris();
        break;
    case Qt::Key_Left:
        pushBtn(Left);
        redrawTetris();
        break;
    case Qt::Key_Right:
        pushBtn(Right);
        redrawTetris();
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        pushBtn(Start);
        break;
    case Qt::Key_P:
        pushBtn(Pause);
        break;
    case Qt::Key_Space:
        pushBtn(Action);
        redrawTetris();
        break;
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

