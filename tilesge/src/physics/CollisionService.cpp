//
// Created by DeKinci on 5/9/2020.
//

#include "physics/CollisionService.h"
#include <cmath>
#include "utils/Log.h"

bool CollisionService::checkCollision(AABB &first, AABB &second) {
//    return (first.min.x <= second.max.x && first.max.x >= second.min.x) &&
//           (first.min.y <= second.max.y && first.max.y >= second.min.y) &&
//           (first.min.z <= second.max.z && first.max.z >= second.min.z);
    return (first.min.x < second.max.x && first.max.x > second.min.x) &&
           (first.min.y < second.max.y && first.max.y > second.min.y) &&
           (first.min.z < second.max.z && first.max.z > second.min.z);
}

void CollisionService::resolveCollision(Body &a, Body &b, float deltaTime) {
    // fix penetration
    glm::vec3 normal = glm::normalize(b.getPosition() - a.getPosition());
    float penetration = CollisionService::calculatePenetration(*a.getAabb(), *b.getAabb());

    if (abs(penetration) > STUCK_DEPTH) {
        penetration -= std::copysign(STUCK_DEPTH, penetration);
        glm::vec3 correction = penetration * normal * ((PUSH_PERCENT * deltaTime) / (a.invMass + b.invMass));
        a.addPosition(-correction * a.invMass);
        b.addPosition(correction * b.invMass);
    }

    // finish if both not moving
    if (!a.isMoving() && !b.isMoving()) {
        return;
    }

    // update acceleration
    float summMass = a.invMass + b.invMass;
    glm::vec3 acc = (a.getAcceleration() * b.invMass + b.getAcceleration() * a.invMass) / summMass;
    a.setAcceleration(acc);
    b.setAcceleration(acc);

    // finish if both not moving
    if (!a.isMoving() && !b.isMoving()) {
        return;
    }

    glm::vec3 rv = b.getVelocity() - a.getVelocity();
    // stuck if stuckable
    if (abs(glm::length(rv * deltaTime)) < STUCK_DEPTH) {
        glm::vec3 nSpeed = (a.getVelocity() * b.invMass + b.getVelocity() * a.invMass) / (a.invMass + b.invMass);
        a.setVelocity(nSpeed);
        b.setVelocity(nSpeed);
        Log::info("Stucked to {}", nSpeed.y);
        return;
    }

    // jump if not stucked
    float velAlongNormal = glm::dot(rv, normal);
    if (velAlongNormal <= 0) {
        float e = a.restitution * b.restitution;
        glm::vec3 impulse = -(1 + e) * velAlongNormal / summMass * normal;

        a.addVelocity(-impulse * a.invMass);
        b.addVelocity(impulse * b.invMass);
    }
}

float CollisionService::calculatePenetration(AABB &first, AABB &second) {
    float x = 0;
    if (first.max.x < second.max.x)
        x = first.max.x - second.min.x;
    else if (first.min.x > second.min.x)
        x = first.min.x - second.max.x;

    float y = 0;
    if (first.max.y < second.max.y)
        y = first.max.y - second.min.y;
    else if (first.min.y > second.min.y)
        y = first.min.y - second.max.y;

    float z = 0;
    if (first.max.z < second.max.z)
        z = first.max.z - second.min.z;
    else if (first.min.z > second.min.z)
        z = first.min.z - second.max.z;

    return glm::length(glm::vec3(x, y, z));
}
