//
// Created by DeKinci on 5/9/2020.
//

#ifndef TILESGE_COLLISIONSERVICE_H
#define TILESGE_COLLISIONSERVICE_H

#include "AABB.h"
#include "Body.h"

#define STUCK_DEPTH 0.001f
#define PUSH_PERCENT 10.0f

class CollisionService {
public:
    static bool checkCollision(AABB &first, AABB &second);
    static void resolveCollision(Body &a, Body &b, float deltaTime);

private:
    static float calculatePenetration(AABB &first, AABB &second);
};


#endif //TILESGE_COLLISIONSERVICE_H
