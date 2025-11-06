QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gradientmap
TEMPLATE = app

include(../defs.pri)

SOURCES += \
    main.cpp \
    widget.cpp

HEADERS += \
    widget.h

