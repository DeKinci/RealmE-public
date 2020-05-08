//
// Created by DeKinci on 5/9/2020.
//

#ifndef TILESGE_GAMEAPP_H
#define TILESGE_GAMEAPP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils/Args.h"
#include "utils/Log.h"
#include "graphics/AppWindow.h"
#include "graphics/Camera.h"
#include "game/CubeForge.h"
#include "graphics/FontLoader.h"
#include "physics/NewtonianPhysicsProcessor.h"

class GameApp {
public:
    explicit GameApp(const Args *args);

    void run();

private:
    const Args *args;
    AppWindow *appWindow;
    Camera *camera;
    NewtonianPhysicsProcessor *physicsProcessor;
    std::vector<Body *> *cubes;
    Model *light;
    Font *font;
    static const int fpl = 600;
    float fps[fpl] = {};
    int fpsPointer = 0;

    float deltaTime = 0;
    float lastFrame = 0;

    void setup();

    void loop();

    void keyPressed(int key);
};


#endif //TILESGE_GAMEAPP_H
