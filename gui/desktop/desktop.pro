QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../brick_game/snake/snakeController.cpp \
    ../../brick_game/snake/snakeModel.cpp \
    ../../brick_game/tetris/tetris.c \
    main.cpp \
    mainwindow.cpp \
    snakeView.cpp \
    tetrisView.cpp

HEADERS += \
    ../../brick_game/brick_game.h \
    ../../brick_game/snake/snake.h \
    ../../brick_game/snake/snake.hpp \
    ../../brick_game/tetris/tetris.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../brick_game/snake/record.txt \
    ../../brick_game/tetris/record.txt

RESOURCES += \
    ../../globalResources.qrc \
    resouces.qrc
