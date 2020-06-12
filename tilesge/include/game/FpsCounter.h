//
// Created by DeKinci on 6/12/2020.
//

#ifndef TILESGE_FPSCOUNTER_H
#define TILESGE_FPSCOUNTER_H

#include <cstddef>

class FpsCounter {
public:
    void registerFps(float deltaTime);
    float getFps() const;
private:
    static const size_t fpl = 60;
    float dts[fpl] = {0,};
    size_t fpsPointer = 0;
    size_t filled = 1;

    float cachedFps = 0.f;
};


#endif //TILESGE_FPSCOUNTER_H
