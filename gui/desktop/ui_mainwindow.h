/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *field;
    QGraphicsView *fieldAdditional;
    QFrame *frame;
    QPushButton *startTetris;
    QPushButton *startSnake;
    QLCDNumber *hScore;
    QLCDNumber *score;
    QLCDNumber *level;
    QPushButton *quit;
    QPushButton *pause;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *gameOver;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(612, 800);
        MainWindow->setStyleSheet(QString::fromUtf8("#centralwidget, QGraphicsView {\n"
"background: #1529bd;\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        field = new QGraphicsView(centralwidget);
        field->setObjectName("field");
        field->setGeometry(QRect(20, 20, 352, 702));
        field->setStyleSheet(QString::fromUtf8("background: teal;"));
        field->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        field->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        fieldAdditional = new QGraphicsView(centralwidget);
        fieldAdditional->setObjectName("fieldAdditional");
        fieldAdditional->setGeometry(QRect(390, 20, 200, 140));
        fieldAdditional->setStyleSheet(QString::fromUtf8("background: teal;"));
        fieldAdditional->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        fieldAdditional->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(390, 530, 201, 131));
        frame->setStyleSheet(QString::fromUtf8("QFrame {\n"
"	border: 2px solid black;\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        startTetris = new QPushButton(frame);
        startTetris->setObjectName("startTetris");
        startTetris->setGeometry(QRect(10, 10, 181, 51));
        startTetris->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"     background: #00d200;\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-color: beige;\n"
" }\n"
"\n"
"QPushButton:hover {\n"
"	background: #119711;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background: #186e18;\n"
"}"));
        startSnake = new QPushButton(frame);
        startSnake->setObjectName("startSnake");
        startSnake->setGeometry(QRect(10, 70, 181, 51));
        startSnake->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"     background: #00d200;\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-color: beige;\n"
" }\n"
"\n"
"QPushButton:hover {\n"
"	background: #119711;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background: #186e18;\n"
"}"));
        hScore = new QLCDNumber(centralwidget);
        hScore->setObjectName("hScore");
        hScore->setGeometry(QRect(390, 250, 201, 41));
        hScore->setStyleSheet(QString::fromUtf8("background: white;"));
        score = new QLCDNumber(centralwidget);
        score->setObjectName("score");
        score->setGeometry(QRect(390, 330, 201, 41));
        score->setStyleSheet(QString::fromUtf8("background: white;"));
        level = new QLCDNumber(centralwidget);
        level->setObjectName("level");
        level->setGeometry(QRect(390, 410, 201, 41));
        level->setStyleSheet(QString::fromUtf8("background: white;"));
        quit = new QPushButton(centralwidget);
        quit->setObjectName("quit");
        quit->setGeometry(QRect(390, 678, 201, 41));
        quit->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"     background: #d22600;\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-color: beige;\n"
" }\n"
"\n"
"QPushButton:hover {\n"
"	background: #bd3315;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background: #972911;\n"
"}"));
        pause = new QPushButton(centralwidget);
        pause->setObjectName("pause");
        pause->setGeometry(QRect(390, 470, 201, 41));
        pause->setAutoFillBackground(false);
        pause->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"     background: #c0c0c0;\n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-color: beige;\n"
" }\n"
"\n"
"QPushButton:hover {\n"
"	background: #9a9a9a;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background: #7b7b7b;\n"
"}"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(390, 389, 71, 21));
        label->setStyleSheet(QString::fromUtf8("background: white;\n"
"padding-left: 5px;\n"
"border-top-left-radius: 10px"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(390, 310, 71, 21));
        label_2->setStyleSheet(QString::fromUtf8("background: white;\n"
"padding-left: 5px;\n"
"border-top-left-radius: 10px"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(390, 230, 111, 21));
        label_3->setStyleSheet(QString::fromUtf8("background: white;\n"
"padding-left: 5px;\n"
"border-top-left-radius: 10px"));
        gameOver = new QLabel(centralwidget);
        gameOver->setObjectName("gameOver");
        gameOver->setEnabled(true);
        gameOver->setGeometry(QRect(390, 170, 201, 41));
        gameOver->setStyleSheet(QString::fromUtf8("color: white"));
        gameOver->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 612, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        startTetris->setText(QCoreApplication::translate("MainWindow", "TETRIS", nullptr));
        startSnake->setText(QCoreApplication::translate("MainWindow", "SNAKE", nullptr));
        quit->setText(QCoreApplication::translate("MainWindow", "QUIT", nullptr));
        pause->setText(QCoreApplication::translate("MainWindow", "PAUSE", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "LEVEL", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "SCORE", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "HIGH SCORE", nullptr));
        gameOver->setText(QCoreApplication::translate("MainWindow", "TO START NEW GAME \n"
"PRESS ENTER", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
