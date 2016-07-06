TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

exists(../common.pri) {
    include(../common.pri)
}

SOURCES += \
    opengl_tex.cpp \    
    helpers.cpp

HEADERS += \    
    helpers.h

DISTFILES += \
    shaders/tex.frag \
    shaders/tex.vert

