#include "helpers.h"

#include <cstdlib>
#include <ctime>

GLfloat randFloat() {
    return GLfloat(rand() % 2000 - 1000)/100.0f;
}

std::vector<glm::vec2> randVertices(size_t num) {
    std::vector<glm::vec2> result(num);
    srand((unsigned)time(0));
    for (size_t i = 0; i < result.size(); i++) {
        result[i] = glm::vec2(randFloat(), randFloat());
    }
    return result;
}

std::vector<glm::vec3> randColors(size_t num) {
    static const GLfloat colors[][3] = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f},
                                        {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f},
                                        {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};
    static const int num_of_colors = sizeof(colors)/(3*sizeof(GLfloat));

    std::vector<glm::vec3> result(num);
    srand((unsigned)time(0));
    for (size_t i = 0; i < num; i++) {
        const GLfloat *color = colors[rand() % num_of_colors];
        result[i] = glm::vec3(color[0], color[1], color[2]);
    }
    return result;
}
