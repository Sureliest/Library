#-------------------------------------------------
#
# Project created by QtCreator 2020-05-18T08:55:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = helloworld
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    dialog.cpp \
    dialog1.cpp \
    library.cpp \
    lend.cpp \
    return.cpp \
    checkkind.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    dialog.h \
    dialog1.h \
    book.h \
    user.h \
    library.h \
    lend.h \
    return.h \
    log.h \
    address.h \
    checkkind.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    dialog.ui \
    dialog1.ui \
    library.ui \
    lend.ui \
    return.ui \
    checkkind.ui

RESOURCES += \
    images.qrc
