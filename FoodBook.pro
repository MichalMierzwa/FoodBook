#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T20:43:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FoodBook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ingredientcombobox.cpp \
    categorycombobox.cpp \
    recipe.cpp

HEADERS  += mainwindow.h \
    ingredientcombobox.h \
    categorycombobox.h \
    recipe.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc

