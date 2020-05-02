//
// Created by DeKinci on 5/1/2020.
//

#ifndef TILESGE_POSITION_H
#define TILESGE_POSITION_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Position {
public:
    Position(float x, float y, float z, float rx, float ry, float rz, float rAngle);

    glm::vec3 getCoords();
    glm::vec3 getRotation();

    float getRotationAngle();
private:
    glm::vec3 coords;
    glm::vec3 rotation;
    float rotationAngle;
};


#endif //TILESGE_POSITION_H
