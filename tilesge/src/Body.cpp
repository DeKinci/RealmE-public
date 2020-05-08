//
// Created by DeKinci on 5/3/2020.
//

#include "Body.h"

Body::Body(Model &model, const glm::vec3 &position) : model{model}, position{position} {
    model.setPosition(position);
}

void Body::setPosition(const glm::vec3 &position) {
    Body::position = position;
    model.setPosition(position);
}

void Body::setVelocity(const glm::vec3 &velocity) {
    Body::velocity = velocity;
    updateMovingFlag();
}

void Body::setAcceleration(const glm::vec3 &acceleration) {
    Body::acceleration = acceleration;
    updateMovingFlag();
}

void Body::addPosition(const glm::vec3 &delta) {
    position += delta;
    model.setPosition(position);
}

void Body::addVelocity(const glm::vec3 &delta) {
    velocity += delta;
    updateMovingFlag();
}

void Body::addAcceleration(const glm::vec3 &delta) {
    acceleration += delta;
    updateMovingFlag();
}

void Body::show(Camera &camera) {
    model.show(camera);
}

const glm::vec3 &Body::getPosition() const {
    return position;
}

const glm::vec3 &Body::getVelocity() const {
    return velocity;
}

const glm::vec3 &Body::getAcceleration() const {
    return acceleration;
}

bool Body::isMoving() {
    return moving;
}

void Body::updateMovingFlag() {
    moving = glm::length2(acceleration) >= EPSILON_SQ || glm::length2(velocity) >= EPSILON_SQ;
}
