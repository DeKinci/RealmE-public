//
// Created by DeKinci on 5/4/2020.
//

#include "physics/NewtonianPhysicsProcessor.h"

#include "utils/Log.h"
#include "physics/CollisionService.h"


NewtonianPhysicsProcessor::NewtonianPhysicsProcessor(size_t cores) :
        queued{*new std::vector<std::future<void>>()},
        threadPool{*new ThreadPool(cores)},
        cores{cores} {
}

void NewtonianPhysicsProcessor::updatePositions(float deltaTime, std::vector<Body *> &bodies) {
    size_t load = bodies.size() / cores;
    Log::debug("load {} size {} batched {}", load, bodies.size(), load * (cores - 1));

    queued.emplace_back(threadPool.enqueue(updateSomePositions, deltaTime, bodies, (cores - 1) * load, bodies.size()));
    for (size_t i = 0; i < cores - 1; i++) {
        queued.emplace_back(threadPool.enqueue(updateSomePositions, deltaTime, bodies, i * load, (i + 1) * load));
    }

    for (auto &f : queued)
        f.get();
    queued.clear();
    Log::debug("physics processed");
}

void NewtonianPhysicsProcessor::updateSomePositions(float deltaTime, const std::vector<Body *> &bodies, size_t start,
                                                    size_t end) {
    for (size_t i = 0; i < bodies.size(); i++) {
        auto first = bodies[i];
        glm::vec3 acc = first->getAcceleration();
        glm::vec3 vel = first->getVelocity();

        glm::vec3 dSpeed = acc * deltaTime;
        glm::vec3 nextPos = first->getPosition() + vel * deltaTime + dSpeed * deltaTime;

        first->setPosition(nextPos);
        first->setVelocity(vel + dSpeed);

        for (size_t j = 0; j < i; j++) {
            auto second = bodies[j];
            if (CollisionService::checkCollision(*first->getAabb(), *second->getAabb())) {
                CollisionService::resolveCollision(*first, *second);
            }
        }
    }
}

