//
// Created by DeKinci on 5/1/2020.
//

#include "Position.h"

Position::Position(float x, float y, float z, float rx, float ry, float rz, float rAngle) :
        coords(glm::vec3(x, y, z)),
        rotation(glm::vec3(rx, ry, rz)),
        rotationAngle(glm::radians(rAngle)) {
}

glm::vec3 Position::getCoords() {
    return coords;
}

glm::vec3 Position::getRotation() {
    return rotation;
}

float Position::getRotationAngle() {
    return rotationAngle;
}