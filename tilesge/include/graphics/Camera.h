//
// Created by DeKinci on 8/11/2019.
//

#ifndef TILESGE_CAMERA_H
#define TILESGE_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Direction.h"

class Camera {
public:
    const float MIN_PITCH = -89.0f, MAX_PITCH = 89.0f;
    const float Z_NEAR = 0.1f, Z_FAR = 100.0f;
    float minFov = 1.0f, maxFov = 45.0f;

    void move(Direction direction, float amount);

    glm::mat4 getProjection();

    glm::mat4 getView();

    void setFov(float fov);

    void changeFov(float offset);

    void setYaw(float yaw);

    void changeYaw(float offset);

    void setPitch(float pitch);

    void changePitch(float offset);

    void setPos(glm::vec3 pos);

    void setFront(glm::vec3 front);

    void setUp(glm::vec3 up);

    void setAspectRatio(float aspectRatio);

private:
    void updateYaw();

    void updatePitch();

    float fov = 45.0f;
    float aspectRatio = 1.0f;
    bool fovChanged = true, aspectRatioChanged = true;

    float yaw = 0.0f;
    float pitch = 0.0f;

    double yawCos = cos(glm::radians(yaw));
    double yawSin = sin(glm::radians(yaw));
    double pitchCos = cos(glm::radians(pitch));

    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    bool posChanged = true, frontChanged = true, upChanged = true;

    glm::mat4 view;
    glm::mat4 projection;
};

#endif //TILESGE_CAMERA_H
