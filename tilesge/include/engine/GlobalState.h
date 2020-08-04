//
// Created by DeKinci on 6/27/2020.
//

#ifndef TILESGE_GLOBALSTATE_H
#define TILESGE_GLOBALSTATE_H

#include "BufferState.h"
#include "mutex"

class GlobalState {
public:
    explicit GlobalState(std::vector<Body *> &bodies);
    BufferState& getFront();
    BufferState& getBack();
    void swap();
private:
    std::mutex mutex;
    BufferState *front;
    BufferState *back;
};


#endif //TILESGE_GLOBALSTATE_H
