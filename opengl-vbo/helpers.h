#pragma once

#include "mygl.h"

#include <vector>
#include <cstddef>

GLfloat randFloat();
std::vector<GLfloat> randVertices(size_t num);
std::vector<GLfloat> randColors(size_t num);
std::vector<GLuint> range(size_t size);
