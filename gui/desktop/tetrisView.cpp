#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::playTetris() {
    timer = new QTimer(this);
    timer->setInterval(830);
    QObject::connect(timer, &QTimer::timeout, this, &MainWindow::tetrisTick);
    timer->start();

    startNewGameTetris();
    redrawTetris();
}

void MainWindow::tetrisTick() {
    setFocus();
    pushBtn(UserAction_t::Timer);
    redrawTetris();
    GameInfo_t info = updateCurrentState();
    timer->stop();
    timer->setInterval(830 - 60 * info.level);
    timer->start();
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
    case ' ':
        pushBtn(Action);
        redrawTetris();
        break;
    }
}


