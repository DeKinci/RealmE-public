//
// Created by DeKinci on 5/9/2020.
//

#include "graphics/Projector.h"
#include <glm/gtc/matrix_transform.hpp>

void Projector::updateDimensions(unsigned int width, unsigned int height) {
    projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
}

glm::mat4 Projector::getProjection() {
    return projection;
}
