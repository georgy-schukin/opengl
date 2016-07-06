TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

exists(../common.pri) {
    include(../common.pri)
}

SOURCES += opengl_vbo.cpp \
    helpers.cpp

HEADERS += \
    helpers.h
