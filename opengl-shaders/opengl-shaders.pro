TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

exists(../deps.pri) {
    include(../deps.pri)
}

INCLUDEPATH += ../

LIBS += -L../mygl -lmygl

unix {
    LIBS += -lGL -lGLU -lglut -lGLEW
}

win32 {
    LIBS += -lopengl32 -lglu32 -lfreeglut -lglew32
}

SOURCES += opengl_shaders.cpp \
    helpers.cpp

HEADERS += \
    helpers.h

DISTFILES += \
    shaders/basic.frag \
    shaders/basic.vert
