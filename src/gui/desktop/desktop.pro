QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    tetrusUI.cpp \
    ../../brick_game/tetris/backend.c \
    ../../brick_game/snake/controller/controller.cpp \
    ../../brick_game/snake/model/model.cpp \
    snakeUI.cpp \


HEADERS += \
    mainwindow.h \
    tetrisUI.h \
    ../../brick_game/tetris/backend.h \
    ../../brick_game/snake/controller/controller.h \
    ../../brick_game/snake/model/model.h \
    ../../brick_game/commom/common.h \
    snakeUI.h \


FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    desktop_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
