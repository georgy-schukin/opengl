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
    helpers.cpp \
    shader.cpp \
    shader_program.cpp \
    opengl_3d.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    helpers.h \
    shader.h \
    shader_program.h \
    mygl.h

DISTFILES += \
    shaders/basic.frag \
    shaders/basic.vert
