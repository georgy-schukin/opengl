#include "mygl/mygl.h"
#include "mygl/shader.h"
#include "mygl/shader_program.h"
#include "helpers.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

GLuint vao, vbo[2];
GLuint texture;
mygl::Shader *vert_shader = 0, *frag_shader = 0;
mygl::ShaderProgram *shader_program = 0;

void initVBO() {
    glGenVertexArrays(1, &vao); // generate one VAO (to store all bindings)
    glGenBuffers(2, vbo); // VBOs for vertices and indices

    GLfloat vertices[][2] = {{0.0f, 0.0f},
                             {1.0f, 0.0f},
                             {1.0f, 1.0f},
                             {0.0f, 1.0f}};

    GLushort indices[] = {0, 1, 2,
                          2, 3, 0};

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0)); // data for attrib 0 (vertices)

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);

    glBindVertexArray(0); // unbind VAO
}

void initMVP() {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 0.0f, -1.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);

    glm::mat4 mvp = projection * view * model;

    const GLint mvp_location = shader_program->getUniformLocation("MVP");
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
}

void initTexture() {
    glGenTextures(1, &texture);

    const size_t tex_size = 128;
    //std::vector<glm::vec3> tex = colorRange(tex_size, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    std::vector<glm::vec3> tex = rainbow(tex_size);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_1D, texture);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB32F, tex.size(), 0, GL_RGB, GL_FLOAT, &tex[0]);

    const GLint tex_location = shader_program->getUniformLocation("colorTex");
    glUniform1i(tex_location, 0);
}

void initShaders() {
    shader_program = new mygl::ShaderProgram();
    vert_shader = new mygl::Shader(GL_VERTEX_SHADER, "shaders/tex.vert");
    frag_shader = new mygl::Shader(GL_FRAGMENT_SHADER, "shaders/tex.frag");

    shader_program->attachShader(vert_shader);
    shader_program->attachShader(frag_shader);

    shader_program->bindAttribLocation("vert", 0);

    shader_program->link();
    shader_program->use();

    initVBO();
    initTexture();
    initMVP();
}

void initGL() {
    glClearColor(0.5f, 0.5f, 0.8f, 1.0f);

    initShaders();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
}

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(0);

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
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);

    glutInitContextVersion(3, 3);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutCreateWindow("OpenGL shader texture");

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
