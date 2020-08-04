//
// Created by DeKinci on 6/27/2020.
//

#include "engine/GlobalState.h"

GlobalState::GlobalState(std::vector<Body *> &bodies) {
    front = new BufferState(bodies);
    back = new BufferState(bodies);
}

void GlobalState::swap() {
//    std::lock_guard<std::mutex> guard(mutex);

    BufferState* tmp = front;
    front = back;
    back = tmp;
}

BufferState &GlobalState::getFront() {
    return *front;
}

BufferState &GlobalState::getBack() {
    return *back;
}
