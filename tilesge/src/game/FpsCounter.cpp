//
// Created by DeKinci on 6/12/2020.
//

#include "game/FpsCounter.h"

void FpsCounter::registerFps(double deltaTime) {
    cachedFps += deltaTime - dts[fpsPointer];
    dts[fpsPointer] = deltaTime;
    fpsPointer = (fpsPointer + 1) % fpl;

    if (filled < fpl)
        filled++;
}

double FpsCounter::getFps() const {
    return filled / cachedFps;
}
