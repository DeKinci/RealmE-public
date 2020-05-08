//
// Created by DeKinci on 8/11/2019.
//

#include "graphics/Camera.h"

void Camera::move(Direction direction, float amount) {
    switch (direction) {
        case Direction::FRONT:
            pos += amount * front;
            break;
        case Direction::BACK:
            pos -= amount * front;
            break;
        case Direction::LEFT:
            pos -= glm::normalize(glm::cross(front, up)) * amount;
            break;
        case Direction::RIGHT:
            pos += glm::normalize(glm::cross(front, up)) * amount;
            break;
        case Direction::UP:
            pos += amount * up;
            break;
        case Direction::DOWN:
            pos -= amount * up;
            break;
    }
    posChanged = true;
}

glm::mat4 Camera::getView() {
    if (posChanged || frontChanged || upChanged) {
        view = glm::lookAt(pos, pos + front, up);

        posChanged = false;
        frontChanged = false;
        upChanged = false;
    }

    return view;
}

glm::mat4 Camera::getProjection() {
    if (fovChanged || aspectRatioChanged) {
        projection = glm::perspective(glm::radians(fov), aspectRatio, Z_NEAR, Z_FAR);
        fovChanged = false;
        aspectRatioChanged = false;
    }
    return projection;
}

void Camera::setFov(float fov) {
    if (this->fov != fov) {
        if (fov <= this->minFov)
            fov = this->minFov;
        if (fov >= this->maxFov)
            fov = this->maxFov;
        this->fov = fov;
        fovChanged = true;
    }
}

void Camera::changeFov(float offset) {
    if (offset != 0.0f) {
        fov += offset;
        if (fov <= minFov)
            fov = minFov;
        if (fov >= maxFov)
            fov = maxFov;

        fovChanged = true;
    }
}

void Camera::setYaw(float yaw) {
    if (yaw != this->yaw) {
        this->yaw = yaw;
        updateYaw();
    }
}

void Camera::changeYaw(float offset) {
    if (offset != 0.0f) {
        yaw += offset;
        updateYaw();
    }
}

void Camera::setPitch(float pitch) {
    if (this->pitch != pitch) {
        if (pitch > MAX_PITCH)
            pitch = MAX_PITCH;
        if (pitch < MIN_PITCH)
            pitch = MIN_PITCH;
        this->pitch = pitch;
        updatePitch();
    }
}

void Camera::changePitch(float offset) {
    if (offset != 0.0f) {
        pitch += offset;
        if (pitch > MAX_PITCH)
            pitch = MAX_PITCH;
        if (pitch < MIN_PITCH)
            pitch = MIN_PITCH;
        updatePitch();
    }
}

void Camera::updateYaw() {
    yawCos = cos(glm::radians(this->yaw));
    yawSin = sin(glm::radians(this->yaw));

    front.x = yawCos * pitchCos;
    front.z = yawSin * pitchCos;
    frontChanged = true;
}

void Camera::updatePitch() {
    pitchCos = cos(glm::radians(pitch));

    front.x = yawCos * pitchCos;
    front.y = sin(glm::radians(pitch));
    front.z = yawSin * pitchCos;
    frontChanged = true;
}

void Camera::setPos(glm::vec3 pos) {
    this->pos = pos;
    posChanged = true;
}

void Camera::setFront(glm::vec3 front) {
    this->front = front;
    frontChanged = true;
}

void Camera::setUp(glm::vec3 up) {
    this->up = up;
    upChanged = true;
}

void Camera::setAspectRatio(float aspectRatio) {
    this->aspectRatio = aspectRatio;
    aspectRatioChanged = true;
}
