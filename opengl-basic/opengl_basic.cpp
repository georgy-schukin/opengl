#include "mygl/mygl.h"

#include <GL/freeglut.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

GLfloat randFloat() {
    return GLfloat(rand() % 2000 - 1000)/100.0f;
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void draw(void) {
    static GLfloat colors[][3] = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f},
                                 {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f},
                                 {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};
    static int num_of_colors = sizeof(colors)/(3*sizeof(GLfloat));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3*25; i++) {
        glColor3fv(colors[rand() % num_of_colors]);
        glVertex2f(randFloat(), randFloat());
    }
    glEnd();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
        exit(0);
    }
}

void initGL() {
    glClearColor(0.5f, 0.5f, 0.8f, 1.0f);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);

    glutInitContextVersion(3, 3);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutCreateWindow("OpenGL basic");

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "GLEW init error!";
        return -1;
    }

    glutReshapeFunc(reshape);
    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);  

    initGL();

    glutMainLoop();
    return 0;
}
