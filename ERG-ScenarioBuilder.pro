#-------------------------------------------------
#
# Project created by QtCreator 2013-03-25T23:16:13
#
#-------------------------------------------------

QT       += core gui script

TARGET = ERG-ScenarioBuilder
TEMPLATE = app


SOURCES += src/main.cpp        \
    src/mainwindow.cpp         \
    src/scenariowidget.cpp     \
    src/playerdialog.cpp

HEADERS  += src/mainwindow.h   \
    src/scenario.h             \
    src/scenariowidget.h       \
    src/playerdialog.h

FORMS    += src/mainwindow.ui  \
    src/scenariowidget.ui      \
    src/playerdialog.ui
