

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BinarySearchTree
TEMPLATE = app


SOURCES += main.cpp\
    binarysearchtree.cpp \
        mainwindow.cpp \
    renderarea.cpp

HEADERS  += mainwindow.h \
    binarysearchtree.h \
    renderarea.h

FORMS    +=
