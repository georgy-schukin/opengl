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
    LIBS += -lopengl32 -lglu32 -lglew32 -lfreeglut
}

SOURCES += opengl_basic.cpp


