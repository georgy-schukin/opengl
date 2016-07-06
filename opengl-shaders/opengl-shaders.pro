TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

exists(../common.pri) {
    include(../common.pri)
}

SOURCES += opengl_shaders.cpp \
    helpers.cpp

HEADERS += \
    helpers.h

DISTFILES += \
    shaders/basic.frag \
    shaders/basic.vert
