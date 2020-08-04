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

void CollisionService::resolveOneSided(const Body &impactor, Body &impactee, const float deltaTime) {
    // fix penetration
    glm::vec3 normal = glm::normalize(impactee.getPosition() - impactor.getPosition());
    float penetration = CollisionService::calculatePenetration(*impactor.getAabb(), *impactee.getAabb());

    if (abs(penetration) > STUCK_DEPTH) {
        penetration -= std::copysign(STUCK_DEPTH, penetration);
        glm::vec3 correction =
                penetration * normal * ((PUSH_PERCENT * deltaTime) / (impactor.invMass + impactee.invMass));
        impactee.addPosition(correction * impactee.invMass);
    }

    // finish if both not moving
    if (!impactor.isMoving() && !impactee.isMoving()) {
        return;
    }

    // update acceleration
    float summMass = impactor.invMass + impactee.invMass;
    glm::vec3 acc =
            (impactor.getAcceleration() * impactee.invMass + impactee.getAcceleration() * impactor.invMass) / summMass;
    impactee.setAcceleration(acc);

    // finish if both not moving
    if (!impactor.isMoving() && !impactee.isMoving()) {
        return;
    }

    glm::vec3 rv = impactee.getVelocity() - impactor.getVelocity();
    // stuck if slow
    if (abs(glm::length(rv * deltaTime)) < STUCK_DEPTH) {
        glm::vec3 nSpeed = (impactor.getVelocity() * impactee.invMass + impactee.getVelocity() * impactor.invMass) /
                           (impactor.invMass + impactee.invMass);
        impactee.setVelocity(nSpeed);
        return;
    }

    // jump if not stuck
    float velAlongNormal = glm::dot(rv, normal);
    if (velAlongNormal <= 0) {
        float e = impactor.restitution * impactee.restitution;
        glm::vec3 impulse = -(1 + e) * velAlongNormal / summMass * normal;
        impactee.addVelocity(impulse * impactee.invMass);
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
