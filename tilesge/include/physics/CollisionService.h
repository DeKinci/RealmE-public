//
// Created by DeKinci on 5/9/2020.
//

#ifndef TILESGE_COLLISIONSERVICE_H
#define TILESGE_COLLISIONSERVICE_H

#include "AABB.h"
#include "Body.h"

class CollisionService {
public:
    static bool checkCollision(AABB &first, AABB &second);
    static void resolveCollision(Body &a, Body &b);
};


#endif //TILESGE_COLLISIONSERVICE_H
