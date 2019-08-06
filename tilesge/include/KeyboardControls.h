//
// Created by DeKinci on 8/6/2019.
//

#ifndef TILESGE_KEYBOARDCONTROLS_H
#define TILESGE_KEYBOARDCONTROLS_H

#include <glm/glm.hpp>

class KeyboardControls {
public:
    glm::vec3 position = glm::vec3(0, 0, 5);
// horizontal angle : toward -Z
    float horizontalAngle = 3.14f;
// vertical angle : 0, look at the horizon
    float verticalAngle = 0.0f;
// Initial Field of View
    float initialFoV = 45.0f;

    float speed = 3.0f; // 3 units / second
    float mouseSpeed = 0.005f;
};


#endif //TILESGE_KEYBOARDCONTROLS_H
