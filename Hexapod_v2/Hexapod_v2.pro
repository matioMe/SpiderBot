TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    leg.cpp \
    point.cpp \
    hexapod.cpp \
    raspberry.cpp \
    network.cpp \
    xml.cpp

HEADERS += \
    leg.h \
    point.h \
    const.h \
    hexapod.h \
    raspberry.h \
    network.h \
    xml.h
