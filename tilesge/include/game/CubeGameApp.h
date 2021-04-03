//
// Created by DeKinci on 4/3/2021.
//

#ifndef TILESGE_CUBEGAMEAPP_H
#define TILESGE_CUBEGAMEAPP_H

#include "GameApp.h"
#include "physics/NewtonianPhysicsProcessor.h"
#include "graphics/FontLoader.h"
#include "physics/NewtonianPhysicsProcessor.h"
#include "game/FpsCounter.h"
#include "game/CubeForge.h"
#include "input/KeyboardManager.h"

class CubeGameApp : public GameApp {
public:
    explicit CubeGameApp(const Args *args);
    ~CubeGameApp() override;

protected:
    void loop() override;

private:
    KeyboardManager *keyboardManager;
    NewtonianPhysicsProcessor *physicsProcessor;
    GlobalState *gs;
    Body *light;

    Direction direction = Direction::FRONT;
    float speed = 0;

    static std::vector<Body *> *generateCubeMap();
    static void generateTree(std::vector<Body *> *vector, int x, int y, int z);
};


#endif //TILESGE_CUBEGAMEAPP_H
