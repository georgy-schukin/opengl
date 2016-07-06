TEMPLATE = lib
CONFIG += static
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR=$$PWD

exists(../deps.pri) {
    include(../deps.pri)
}

unix {
    LIBS += -lGL -lGLU -lGLEW
}

win32 {
    LIBS += -lopengl32 -lglu32 -lglew32
}

SOURCES += \
    shader.cpp \
    shader_program.cpp \

HEADERS += \
    mygl.h \
    shader.h \
    shader_program.h 
