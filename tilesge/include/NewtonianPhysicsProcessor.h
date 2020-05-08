//
// Created by DeKinci on 5/4/2020.
//

#ifndef FREETYPE_NEWTONIANPHYSICSPROCESSOR_H
#define FREETYPE_NEWTONIANPHYSICSPROCESSOR_H

#include <vector>
#include <glm/gtx/norm.hpp>

#include "Log.h"
#include "Body.h"
#include "ThreadPool.h"

#define EPSILON_SQ 0.001

class NewtonianPhysicsProcessor {
public:
    explicit NewtonianPhysicsProcessor(size_t cores);
    void updatePositions(float deltaTime, std::vector<Body *> &bodies);

private:
    size_t cores;
    ThreadPool &threadPool;
    std::vector<std::future<void>> &queued;

    static void updateSomePositions(float deltaTime, const std::vector<Body *> &bodies, size_t start, size_t end);
};


#endif //FREETYPE_NEWTONIANPHYSICSPROCESSOR_H
