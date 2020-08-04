//
// Created by DeKinci on 5/9/2020.
//

#ifndef TILESGE_GAMEAPP_H
#define TILESGE_GAMEAPP_H

#include "utils/Args.h"
#include "graphics/AppWindow.h"
#include "graphics/Camera.h"
#include "graphics/FontLoader.h"
#include "physics/NewtonianPhysicsProcessor.h"
#include "game/FpsCounter.h"

class GameApp {
public:
    explicit GameApp(const Args *args);

    void run();

private:
    const Args *args;
    AppWindow *appWindow;
    Camera *camera;
    NewtonianPhysicsProcessor *physicsProcessor;
    GlobalState *gs;
    Model *light;
    Font *font;

    FpsCounter fps = FpsCounter();

    Direction direction = Direction::FRONT;
    float speed = 0;

    float deltaTime = 0;
    float lastFrame = 0;

    void setup();

    void loop();

    void keyPressed(int key);
};


#endif //TILESGE_GAMEAPP_H
