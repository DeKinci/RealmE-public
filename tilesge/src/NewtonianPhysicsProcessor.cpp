//
// Created by DeKinci on 5/4/2020.
//

#include "NewtonianPhysicsProcessor.h"

NewtonianPhysicsProcessor::NewtonianPhysicsProcessor(size_t cores) {
    threadPool = new ThreadPool(cores);
}

void NewtonianPhysicsProcessor::updatePositions(float deltaTime, std::vector<Body *> &bodies) {
    int size = bodies.size();
    int n = 7;
    int load = size / n;

    void (*p)(std::vector<Body *> &, float, int, int) = [](std::vector<Body *> &vector, float deltaTime, int start,
                                                           int end) {
        NewtonianPhysicsProcessor::updateSomePositions(deltaTime, vector, start, end);
    };

    std::vector<std::future<void>> queued;
    for (int i = 0; i < n - 1; i++) {
        int start = i * load;
        int end = (i + 1) * load;

        threadPool->enqueue(p, bodies, deltaTime, start, end);
        queued.emplace_back(threadPool->enqueue(p, bodies, deltaTime, start, end));
    }

    queued.emplace_back(threadPool->enqueue(p, bodies, deltaTime, (n - 1) * load, size));


    for (auto &f : queued)
        f.get();
}

void NewtonianPhysicsProcessor::updateSomePositions(float deltaTime, const std::vector<Body *> &bodies, size_t start,
                                                    size_t end) {
    for (size_t i = start; i < end; i++) {
        glm::vec3 acc = bodies[i]->getAcceleration();
        glm::vec3 vel = bodies[i]->getVelocity();
        if (glm::length(acc) < EPSILON_SQ && glm::length(vel) < EPSILON_SQ)
            continue;

        glm::vec3 dSpeed = acc * deltaTime;
        glm::vec3 nextPos = bodies[i]->getPosition() + vel * deltaTime + dSpeed * deltaTime;

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

        bodies[i]->setPosition(nextPos);
        bodies[i]->setVelocity(vel + dSpeed);
    }
}

