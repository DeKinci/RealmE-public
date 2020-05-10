//
// Created by DeKinci on 5/9/2020.
//

#ifndef TILESGE_AABB_H
#define TILESGE_AABB_H

#include <glm/vec3.hpp>
class AABB {
public:
    AABB(const glm::vec3 &min, const glm::vec3 &max);

    glm::vec3 min;
    glm::vec3 max;
};


#endif //TILESGE_AABB_H
