//
// Created by DeKinci on 5/9/2020.
//

#include "physics/CollisionService.h"
#include <glm/glm.hpp>
#include <cmath>

bool CollisionService::checkCollision(AABB &first, AABB &second) {
    return (first.min.x <= second.max.x && first.max.x >= second.min.x) &&
           (first.min.y <= second.max.y && first.max.y >= second.min.y) &&
           (first.min.z <= second.max.z && first.max.z >= second.min.z);
//    return (first.min.x < second.max.x && first.max.x > second.min.x) &&
//           (first.min.y < second.max.y && first.max.y > second.min.y) &&
//           (first.min.z < second.max.z && first.max.z > second.min.z);
}

void CollisionService::resolveCollision(Body &a, Body &b) {
    glm::vec3 rv = b.getVelocity() - a.getVelocity();
    if (glm::length2(rv) < 0.00000001f)
        return;

    glm::vec3 normal = glm::normalize(b.getPosition() - a.getPosition());
    float velAlongNormal = glm::dot(rv, normal);
    if (velAlongNormal > 0)
        return;

    float e = fminf(a.restitution, b.restitution);

    float j = -(1 + e) * velAlongNormal * a.mass * b.mass / (a.mass + b.mass);
    glm::vec3 impulse = j * normal;

    a.addVelocity(-impulse / a.mass);
    b.addVelocity(impulse / b.mass);
}
