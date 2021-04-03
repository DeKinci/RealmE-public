//
// Created by DeKinci on 5/3/2020.
//

#include "physics/Body.h"

Body::Body(GraphicsObject *go, const glm::vec3 &position, float mass) {
    Body::go = go;
    setPosition(position);
    Body::mass = mass;
    invMass = mass == 0 ? 0 : 1.0f / mass;
}

Body::Body(const Body *body){
    Body::go = body->go;
    Body::restitution = body->restitution;
    Body::mass = body->mass;
    Body::invMass = body->invMass;
    Body::position = body->position;
    Body::velocity = body->velocity;
    Body::acceleration = body->acceleration;
    Body::permAcceleration = body->permAcceleration;
    Body::moving = body->moving;
    Body::transormation = body->transormation;
    computeAABB();
}

void Body::merge(const Body *body) {
    Body::restitution = body->restitution;
    Body::mass = body->mass;
    Body::invMass = body->invMass;
    Body::position = body->position;
    Body::velocity = body->velocity;
    Body::acceleration = body->acceleration;
    Body::permAcceleration = body->permAcceleration;
    Body::moving = body->moving;
    Body::transormation = body->transormation;
    computeAABB();
}

void Body::setPosition(const glm::vec3 &position) {
    Body::position = position;
    transormation = glm::mat4(1.0f);
    transormation = glm::translate(transormation, position);
//    transormation = glm::rotate(transormation, position->getRotationAngle(), position->getRotation());

    computeAABB();
}

void Body::setVelocity(const glm::vec3 &velocity) {
    Body::velocity = velocity;
    updateMovingFlag();
}

void Body::setAcceleration(const glm::vec3 &acceleration) {
    Body::acceleration = acceleration;
    updateMovingFlag();
}

void Body::setPermAcceleration(const glm::vec3 &permAcceleration) {
    Body::permAcceleration = permAcceleration;
}

void Body::addPosition(const glm::vec3 &delta) {
    setPosition(position + delta);
}

void Body::addVelocity(const glm::vec3 &delta) {
    setVelocity(velocity + delta);
}

void Body::addAcceleration(const glm::vec3 &delta) {
    setAcceleration(acceleration + delta);
}

void Body::show(Camera &camera) {
    go->showAt(camera, transormation);
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

const glm::vec3 &Body::getPermAcceleration() const {
    return permAcceleration;
}

bool Body::isMoving() const {
    return moving;
}

void Body::updateMovingFlag() {
    moving = glm::length2(acceleration) >= EPSILON_SQ || glm::length2(velocity) >= EPSILON_SQ;
    if (!moving) {
        velocity = glm::vec3();
        acceleration = glm::vec3();
    }
}

void Body::computeAABB() {
    delete aabb;
    aabb = new AABB(glm::vec3(-0.5, -0.5, -0.5) + position, glm::vec3(0.5, 0.5, 0.5) + position);
}

AABB *Body::getAabb() const {
    return aabb;
}

Body::~Body() {
    delete aabb;
}

const glm::mat4 &Body::getTransormation() const {
    return transormation;
}
