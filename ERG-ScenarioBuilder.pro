#-------------------------------------------------
#
# Project created by QtCreator 2013-03-25T23:16:13
#
#-------------------------------------------------

QT       += core gui script

TARGET = ERG-ScenarioBuilder
TEMPLATE = app

SOURCES += src/main.cpp                \
    src/widgets/mainwindow.cpp         \
    src/widgets/scenariowidget.cpp     \
    src/widgets/playerdialog.cpp \
    src/widgets/floordialog.cpp \
    src/widgets/floortile.cpp \
    src/widgets/wall.cpp \
    src/mru.cpp \
    src/widgets/logwindow.cpp

HEADERS  += src/widgets/mainwindow.h   \
    src/scenario.h                     \
    src/widgets/scenariowidget.h       \
    src/widgets/playerdialog.h \
    src/widgets/floordialog.h \
    src/widgets/floortile.h \
    src/widgets/wall.h \
    src/mru.h \
    src/widgets/logwindow.h

FORMS    += src/widgets/mainwindow.ui  \
    src/widgets/scenariowidget.ui      \
    src/widgets/playerdialog.ui \
    src/widgets/floordialog.ui \
    src/widgets/floortile.ui
