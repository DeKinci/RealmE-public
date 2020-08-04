//
// Created by DeKinci on 5/4/2020.
//

#ifndef FREETYPE_NEWTONIANPHYSICSPROCESSOR_H
#define FREETYPE_NEWTONIANPHYSICSPROCESSOR_H

#include <vector>
#include <glm/gtx/norm.hpp>

#include "Body.h"
#include "utils/ThreadPool.h"
#include "engine/GlobalState.h"

class NewtonianPhysicsProcessor {
public:
    explicit NewtonianPhysicsProcessor(size_t cores);

    void updatePositions(float deltaTime, GlobalState *state);

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

    static void mapBody(float simDeltaTime, const BufferState &bs, size_t bodyIndex, Body *newBody);
};


#endif //FREETYPE_NEWTONIANPHYSICSPROCESSOR_H
