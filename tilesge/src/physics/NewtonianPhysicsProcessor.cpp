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

void NewtonianPhysicsProcessor::updatePositions(float deltaTime, GlobalState *state) {
    updatePhysSpeed(deltaTime);
    float simulationDeltaTime = deltaTime * currentPhysSpeed;

    auto frontAll = state->getFront().all();
    auto back = state->getBack().all();
    for (size_t i = 0; i < frontAll.size(); i++) {
        mapBody(simulationDeltaTime, state->getFront(), i, back[i]);
    }
}

void NewtonianPhysicsProcessor::mapBody(float simDeltaTime, const BufferState &bs, size_t bodyIndex, Body *newBody) {
    bool collided = false;
    auto bodies = bs.all();
    newBody->merge(bs.all()[bodyIndex]);
    newBody->setAcceleration(newBody->getPermAcceleration());

    for (size_t i = 0; i < bodies.size(); i++) {
        auto second = bodies[i];
        if (i != bodyIndex && CollisionService::checkCollision(*second->getAabb(), *newBody->getAabb())) {
            CollisionService::resolveOneSided(*second, *newBody, simDeltaTime);
            collided = true;
        }
    }

    if (!newBody->isMoving()) {
        return;
    }

    glm::vec3 acc = newBody->getAcceleration();
    glm::vec3 vel = newBody->getVelocity();
    glm::vec3 dSpeed = acc * simDeltaTime;
    glm::vec3 nextPos = newBody->getPosition() + vel * simDeltaTime + dSpeed * simDeltaTime;

    newBody->setPosition(nextPos);
    if (!collided)
        newBody->setVelocity(vel + dSpeed);

    Log::info("Acceleration {} velocity {} position {}", acc.y, newBody->getVelocity().y, nextPos.y);
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
