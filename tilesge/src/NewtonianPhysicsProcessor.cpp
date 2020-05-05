//
// Created by DeKinci on 5/4/2020.
//

#include "NewtonianPhysicsProcessor.h"

void NewtonianPhysicsProcessor::updatePositions(float deltaTime, const std::vector<Body *> &bodies) {
    for (auto body : bodies) {
        glm::vec3 acc = body->getAcceleration();
        glm::vec3 vel = body->getVelocity();
        if (glm::length(acc) < EPSILON_SQ && glm::length(vel) < EPSILON_SQ)
            continue;

        glm::vec3 dSpeed = acc * deltaTime;
        glm::vec3 nextPos = body->getPosition() + vel * deltaTime + dSpeed * deltaTime;

        static float collY = 0;
        static float k = 1.0;
        if (nextPos.y <= collY) {
            float fix = (1 - nextPos.y) * acc.y / vel.y;
            if (abs(vel.y) < abs(fix)) {
                fix = -vel.y;
            }

            vel = glm::vec3(vel.x, -(vel.y + fix) * k, vel.z);
            nextPos = glm::vec3(nextPos.x, 2 * collY - nextPos.y, nextPos.z);
        }

        body->setPosition(nextPos);
        body->setVelocity(vel + dSpeed);
    }
}
