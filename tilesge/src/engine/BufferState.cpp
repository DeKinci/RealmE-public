//
// Created by DeKinci on 6/27/2020.
//

#include "engine/BufferState.h"

#include <utility>

BufferState::BufferState(std::vector<Body *> &bodies) {
    this->bodies = new std::vector<Body *>();
    for (auto b : bodies) {
        this->bodies->push_back(new Body(b));
    }
}

size_t BufferState::addBody(Body &body) {
    bodies->push_back(&body);
    return bodies->size() - 1;
}

const Body &BufferState::getBody(size_t position) const {
    return *bodies->at(position);
}

void BufferState::removeBody(size_t position) {
    bodies->erase(bodies->begin() + position);
}

void BufferState::clear() {
    for (auto *b : *bodies) {
        delete b;
    }
    bodies->clear();
}

const std::vector<Body *> &BufferState::all() const {
    return *bodies;
}
