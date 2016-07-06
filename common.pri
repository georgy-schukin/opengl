exists(deps.pri) {
    include(deps.pri);
}

INCLUDEPATH += ../

LIBS += -L../mygl -lmygl

unix {
    LIBS += -lGL -lGLU -lglut -lGLEW
}

win32 {
    LIBS += -lopengl32 -lglu32 -lfreeglut -lglew32
}
