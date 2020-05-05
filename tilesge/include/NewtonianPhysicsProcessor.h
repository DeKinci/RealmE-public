//
// Created by DeKinci on 5/4/2020.
//

#ifndef FREETYPE_NEWTONIANPHYSICSPROCESSOR_H
#define FREETYPE_NEWTONIANPHYSICSPROCESSOR_H

#include <vector>
#include <glm/gtx/norm.hpp>

#include "Body.h"

#define EPSILON_SQ 0.001

class NewtonianPhysicsProcessor {
public:
    static void updatePositions(float deltaTime, const std::vector<Body *> &bodies);
};


#endif //FREETYPE_NEWTONIANPHYSICSPROCESSOR_H
