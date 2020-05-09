//
// Created by DeKinci on 5/9/2020.
//

#ifndef TILESGE_PROJECTOR_H
#define TILESGE_PROJECTOR_H

#include <glm/mat4x4.hpp>

class Projector {
public:
    void updateDimensions(unsigned int width, unsigned int height);

    glm::mat4 getProjection();

private:
    glm::mat4 projection;
};


#endif //TILESGE_PROJECTOR_H
