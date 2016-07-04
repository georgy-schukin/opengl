#include "mygl.h"
#include "shader.h"
#include "shader_program.h"
#include "helpers.h"

#include <iostream>

GLuint vao, vbo[2];
Shader *vert_shader = 0, *frag_shader = 0;
ShaderProgram *shader_program = 0;

const size_t NUM_OF_TRIANGLES = 25;
const size_t NUM_OF_VERTICES = NUM_OF_TRIANGLES*3;

void initVBO() {
    glGenVertexArrays(1, &vao); // generate one VAO (to store all bindings)
    glGenBuffers(2, vbo); // generate two VBOs (for vertices and colors)

    std::vector<glm::vec2> vertices = randVertices(NUM_OF_VERTICES);
    std::vector<glm::vec3> colors = randColors(NUM_OF_VERTICES);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec2), &vertices[0], GL_STREAM_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0)); // data for attrib 0 (vertices)

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(glm::vec3), &colors[0], GL_STREAM_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0)); // data for attrib 1 (colors)

    glBindVertexArray(0); // unbind VAO
}

void initMVP() {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 0.0f, -1.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 1.0f);

    glm::mat4 mvp = projection * view * model;

    const GLint mvp_location = shader_program->getUniformLocation("MVP");
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
}

void initShaders() {
    shader_program = new ShaderProgram();
    vert_shader = new Shader(GL_VERTEX_SHADER, "shaders/basic.vert");
    frag_shader = new Shader(GL_FRAGMENT_SHADER, "shaders/basic.frag");

    shader_program->attachShader(vert_shader);
    shader_program->attachShader(frag_shader);

    shader_program->bindAttribLocation("vert", 0);
    shader_program->bindAttribLocation("color", 1);

    shader_program->link();
    shader_program->use();

    initVBO();
    initMVP();
}

void drawVBO() {
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, NUM_OF_VERTICES);

    glBindVertexArray(0);
}

void drawShaders() {    
    drawVBO();
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

    drawShaders();

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

    glutCreateWindow("OpenGL shaders");

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
