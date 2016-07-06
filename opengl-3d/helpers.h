#pragma once

#include "mygl/mygl.h"

#include <glm/glm.hpp>
#include <vector>
#include <cstddef>

GLfloat randFloat();
std::vector<glm::vec3> randVertices(size_t num);
std::vector<glm::vec3> randColors(size_t num);
