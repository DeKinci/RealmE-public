//
// Created by DeKinci on 5/4/2020.
//

#ifndef FREETYPE_NEWTONIANPHYSICSPROCESSOR_H
#define FREETYPE_NEWTONIANPHYSICSPROCESSOR_H

#include <vector>
#include <glm/gtx/norm.hpp>

#include "Body.h"
#include "utils/ThreadPool.h"

class NewtonianPhysicsProcessor {
public:
    explicit NewtonianPhysicsProcessor(size_t cores);

    void updatePositions(float deltaTime, std::vector<Body *> &bodies);

    void setPhysSpeed(float newPhysSpeed, bool animate);

private:
    size_t cores;
    ThreadPool &threadPool;
    std::vector<std::future<void>> &queued;
    float currentPhysSpeed = 1;
    float physAcceleration = 0.5;
    float initPhysSpeed = currentPhysSpeed;
    float targetPhysPeed = 1;

    void updatePhysSpeed(float deltaTime);

    static void updateSomePositions(float deltaTime, const std::vector<Body *> &bodies, size_t start, size_t end);
};


#endif //FREETYPE_NEWTONIANPHYSICSPROCESSOR_H
