#-------------------------------------------------
#
# Project created by QtCreator 2024-11-29T15:57:12
#
#-------------------------------------------------
QT       += axcontainer
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = handwriting
TEMPLATE = app
DESTDIR = D:/WPS/Class/LessonsCode/yinxiang/LessonCode/week06/practice/

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH +=C:\MicrosoftTablet\Include

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dlgsettings.cpp \
    handsinput.cpp \
    englishwidget.cpp \
    numberwidget.cpp \
    punctuationwidget.cpp

HEADERS += \
        mainwindow.h \
    dlgsettings.h \
    handsinput.h \
    englishwidget.h \
    numberwidget.h \
    punctuationwidget.h

FORMS += \
        mainwindow.ui \
    dlgsettings.ui
