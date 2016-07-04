#include "helpers.h"

#include <cstdlib>

GLfloat randFloat() {
    return GLfloat(rand() % 2000 - 1000)/100.0f;
}

std::vector<GLfloat> randVertices(size_t num) {
    std::vector<GLfloat> result(2*num);
    for (size_t i = 0; i < result.size(); i++) {
        result[i] = randFloat();
    }
    return result;
}

std::vector<GLfloat> randColors(size_t num) {
    static const GLfloat colors[][3] = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f},
                                        {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f},
                                        {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};
    static const int num_of_colors = sizeof(colors)/(3*sizeof(GLfloat));

    std::vector<GLfloat> result(3*num);
    for (size_t i = 0; i < num; i++) {
        const GLfloat *color = colors[rand() % num_of_colors];
        result[3*i] = color[0];
        result[3*i + 1] = color[1];
        result[3*i + 2]= color[2];
    }
    return result;
}

std::vector<GLuint> range(size_t size) {
    std::vector<GLuint> result(size);
    for (size_t i = 0; i < size; i++)
        result[i] = i;
    return result;
}
