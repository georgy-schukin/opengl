TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

exists(../common.pri) {
    include(../common.pri)
}

SOURCES += \
    helpers.cpp \    
    opengl_3d.cpp

HEADERS += \
    helpers.h

DISTFILES += \
    shaders/basic.frag \
    shaders/basic.vert
