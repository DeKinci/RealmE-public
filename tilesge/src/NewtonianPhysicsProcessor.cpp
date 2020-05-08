//
// Created by DeKinci on 5/4/2020.
//

#include "NewtonianPhysicsProcessor.h"

NewtonianPhysicsProcessor::NewtonianPhysicsProcessor(size_t cores) :
        queued{*new std::vector<std::future<void>>()},
        threadPool{*new ThreadPool(cores)},
        cores{cores} {
}

void NewtonianPhysicsProcessor::updatePositions(float deltaTime, std::vector<Body *> &bodies) {
    size_t load = bodies.size() / cores;
    spdlog::debug("load {} size {} batched {}", load, bodies.size(), load * (cores - 1));

    queued.emplace_back(threadPool.enqueue(updateSomePositions, deltaTime, bodies, (cores - 1) * load, bodies.size()));
    for (size_t i = 0; i < cores - 1; i++) {
        queued.emplace_back(threadPool.enqueue(updateSomePositions, deltaTime, bodies, i * load, (i + 1) * load));
    }

    for (auto &f : queued)
        f.get();
    queued.clear();
    spdlog::debug("physics processed");
}

void NewtonianPhysicsProcessor::updateSomePositions(float deltaTime, const std::vector<Body *> &bodies, size_t start,
                                                    size_t end) {
    for (size_t i = start; i < end; i++) {
        if (!bodies[i]->isMoving())
            continue;

        auto body = bodies[i];
        glm::vec3 acc = body->getAcceleration();
        glm::vec3 vel = body->getVelocity();

        glm::vec3 dSpeed = acc * deltaTime;
        glm::vec3 nextPos = body->getPosition() + vel * deltaTime + dSpeed * deltaTime;

        static float collY = 1;
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

