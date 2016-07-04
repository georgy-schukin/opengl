TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

exists(../deps.pri) {
    include(../deps.pri)
}

unix {
    LIBS += -lGL -lGLU -lglut -lGLEW
}

win32 {
    LIBS += -lopengl32 -lglu32 -lfreeglut -lglew32
}

SOURCES += \
    opengl_tex.cpp \
    shader.cpp \
    shader_program.cpp \
    helpers.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    mygl.h \
    shader.h \
    shader_program.h \
    helpers.h

DISTFILES += \
    shaders/tex.frag \
    shaders/tex.vert

