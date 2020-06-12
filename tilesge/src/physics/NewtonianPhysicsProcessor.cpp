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
    for (auto bod : bodies)
        bod->setAcceleration(bod->getPermAcceleration());

    size_t load = bodies.size() / cores;
    Log::debug("load {} size {} batched {}", load, bodies.size(), load * (cores - 1));
    updatePhysSpeed(deltaTime);
    float simulationDeltaTime = deltaTime * currentPhysSpeed;

    NewtonianPhysicsProcessor::updateSomePositions(simulationDeltaTime, bodies, 0, 0);
//    queued.emplace_back(
//            threadPool.enqueue(updateSomePositions, simulationDeltaTime, bodies, (cores - 1) * load, bodies.size()));
//    for (size_t i = 0; i < cores - 1; i++) {
//        queued.emplace_back(
//                threadPool.enqueue(updateSomePositions, simulationDeltaTime, bodies, i * load, (i + 1) * load));
//    }
//
//    for (auto &f : queued)
//        f.get();
//    queued.clear();
}

void NewtonianPhysicsProcessor::updateSomePositions(float deltaTime, const std::vector<Body *> &bodies, size_t start,
                                                    size_t end) {
    auto collided = new bool[bodies.size()]{};
    for (size_t i = 0; i < bodies.size(); i++) {
        auto first = bodies[i];
        for (size_t j = 0; j < i; j++) {
            auto second = bodies[j];
            if (CollisionService::checkCollision(*first->getAabb(), *second->getAabb())) {
                collided[i] = true;
                collided[j] = true;
                CollisionService::resolveCollision(*first, *second, deltaTime);
            }
        }
    }

    for (size_t i = 0; i < bodies.size(); i++) {
        auto first = bodies[i];

        if (!first->isMoving()) {
            continue;
        }

        glm::vec3 acc = first->getAcceleration();
        glm::vec3 vel = first->getVelocity();
        glm::vec3 dSpeed = acc * deltaTime;
        glm::vec3 nextPos = first->getPosition() + vel * deltaTime + dSpeed * deltaTime;

        first->setPosition(nextPos);
        if (!collided[i])
            first->setVelocity(vel + dSpeed);

        Log::info("Acceleration {} velocity {} position {}", acc.y, first->getVelocity().y, nextPos.y);
    }
}

void NewtonianPhysicsProcessor::updatePhysSpeed(float deltaTime) {
    if (abs(targetPhysPeed - currentPhysSpeed) > 0.001) {
        float delta = (targetPhysPeed - initPhysSpeed) * deltaTime * physAcceleration;
        currentPhysSpeed += delta;
        if (abs(targetPhysPeed - currentPhysSpeed) < delta)
            currentPhysSpeed = targetPhysPeed;
    }
}

void NewtonianPhysicsProcessor::setPhysSpeed(float newPhysSpeed, bool animate) {
    targetPhysPeed = newPhysSpeed;
    initPhysSpeed = currentPhysSpeed;
    if (!animate)
        currentPhysSpeed = newPhysSpeed;
}

