#include "mygl.h"
#include "helpers.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstddef>

GLuint vao, vbo[3];

const size_t NUM_OF_TRIANGLES = 25;
const size_t NUM_OF_VERTICES = NUM_OF_TRIANGLES*3;

void initVBO() {
    glGenVertexArrays(1, &vao); // generate one VAO (to store all bindings)
    glGenBuffers(3, vbo); // generate VBOs (for vertices, colors and indices)

    std::vector<GLfloat> vertices = randVertices(NUM_OF_VERTICES);
    std::vector<GLfloat> colors = randColors(NUM_OF_VERTICES);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // buffer for verices
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), &vertices[0], GL_STREAM_DRAW);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, (void*)(0));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // buffer for colors
    glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(GLfloat), &colors[0], GL_STREAM_DRAW);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, (void*)(0));

    /*std::vector<GLuint> indices = range(NUM_OF_VERTICES);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), &indices[0], GL_STREAM_DRAW);*/

    glBindVertexArray(0); // unbind VAO
}

void drawVBO() {
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, NUM_OF_VERTICES);
    //glDrawElements(GL_TRIANGLES, NUM_OF_VERTICES, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void initGL() {
    glClearColor(0.5f, 0.5f, 0.8f, 1.0f);
    initVBO();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawVBO();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);

    glutInitContextVersion(3, 3);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutCreateWindow("OpenGL VBO");

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
