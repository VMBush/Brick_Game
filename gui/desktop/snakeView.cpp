#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::playSnake() {
    timer = new QTimer(this);
    timer->setInterval(830);
    QObject::connect(timer, &QTimer::timeout, this, snakeTick);
    timer->start();

    ui->gameOver->setVisible(true);

    startNewGameSnake();
    redrawSnake();

}

void MainWindow::snakeTick() {
    setFocus();
    pushBtnSnake(UserAction_t::Timer);
    redrawSnake();
    GameInfo_t info = updateCurrentState();
    timer->stop();
    if (actionPushed) timer->setInterval(200);
    else timer->setInterval(730 - 50 * info.level);
    timer->start();

}

void MainWindow::redrawSnake() {
    QGraphicsScene* newField = new QGraphicsScene;
    newField->setSceneRect(0, 0, ui->field->width(), ui->field->height());

    GameInfo_t info = getStateSnake();
    if (info.end == 1) ui->gameOver->setVisible(true);
    //else ui->gameOver->setVisible(false);

    ui->hScore->display(info.high_score);
    ui->score->display(info.score);
    ui->level->display(info.level);

    int w = ui->field->width() / 10;
    int h = ui->field->height() / 20;
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= 10; j++) {
            if (info.field[i][j] == 0) continue;
            QPixmap pix = getSnakeImg(info.field[i][j]);

            QGraphicsPixmapItem* item = newField->addPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
            item->setPos((j-1)*(w), (i-1)*(h));
        }
    }

    delete field;
    field = newField;
    ui->field->setScene(field);

    QGraphicsScene* newFieldAddition = new QGraphicsScene;
    delete fieldAddition;
    fieldAddition = newFieldAddition;
    ui->fieldAdditional->setScene(fieldAddition);
}

QPixmap getSnakeImg(int type) {
    QPixmap pix;
    switch (type) {
    case 1:
        pix = QPixmap(":/img/img/snake/snake.png");
        break;
    case 2:
        pix = QPixmap(":/img/img/snake/apple.png");
        break;

    default:
        break;
    }

    return pix;
}


void MainWindow::keyPressEventSnake(int key) {
    if (key == Qt::Key_Left) {
        pushBtnSnake(260);
    } else if (key == Qt::Key_Right) {
        pushBtnSnake(261);
    } else if (key == Qt::Key_Up) {
        pushBtnSnake(259);
    } else if (key == Qt::Key_Down) {
        pushBtnSnake(258);
    } else if (key == Qt::Key_Enter || key == Qt::Key_Return) {
        pushBtnSnake(10);
        ui->gameOver->setVisible(false);
    } else {
        pushBtnSnake(key);
    }
}
