//
// Created by DeKinci on 6/27/2020.
//

#ifndef TILESGE_BUFFERSTATE_H
#define TILESGE_BUFFERSTATE_H

#include "physics/Body.h"
#include "vector"

class BufferState {
public:
    explicit BufferState(std::vector<Body *> &bodies);
    size_t addBody(Body &body);
    const Body& getBody(size_t position) const;
    void removeBody(size_t position);
    void clear();
    const std::vector<Body *>& all() const;

private:
    std::vector<Body *> *bodies;
};


#endif //TILESGE_BUFFERSTATE_H
