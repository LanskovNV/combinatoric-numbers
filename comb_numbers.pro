TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/main.cpp \
    src/numbers.cpp \
    src/interface.cpp \
    src/error.cpp

HEADERS += \
    src/numbers.h \
    src/interface.h \
    src/error.h
