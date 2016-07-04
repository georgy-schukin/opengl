#include "helpers.h"

std::vector<glm::vec3> colorRange(size_t size, const glm::vec3 &start, const glm::vec3 &end) {
    std::vector<glm::vec3> result(size);
    for (size_t i = 0; i < size; i++) {
        const float t = float(i)/size;
        result[i] = start*(1.0f - t) + end*t;
    }
    return result;
}

std::vector<glm::vec3> rainbow(size_t segment_size) {
    static const glm::vec3 colors[] = {glm::vec3(1.0f, 0.0f, 1.0f), // purple
                                       glm::vec3(0.0f, 0.0f, 1.0f), // blue
                                       glm::vec3(0.0f, 1.0f, 1.0f), // cyan
                                       glm::vec3(0.0f, 1.0f, 0.0f), // green
                                       glm::vec3(1.0f, 1.0f, 0.0f), // yellow
                                       glm::vec3(1.0f, 0.7f, 0.0f), // orange
                                       glm::vec3(1.0f, 0.0f, 0.0f)}; // red
    std::vector<glm::vec3> result;
    for (int i = 0; i < 6; i++) {
        std::vector<glm::vec3> color_range = colorRange(segment_size, colors[i], colors[i + 1]);
        result.insert(result.end(), color_range.begin(), color_range.end());
    }
    return result;
}
