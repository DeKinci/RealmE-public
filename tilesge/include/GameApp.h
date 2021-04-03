//
// Created by DeKinci on 5/9/2020.
//

#ifndef TILESGE_GAMEAPP_H
#define TILESGE_GAMEAPP_H

#include "utils/Args.h"
#include "graphics/AppWindow.h"
#include "graphics/Font.h"

#include "physics/NewtonianPhysicsProcessor.h"

#include "game/FpsCounter.h"

class GameApp {
public:
    explicit GameApp(const Args *args);

    virtual ~GameApp();

    void run();

protected:
    Camera *camera;
    Projector *projector;
    double deltaTime = 0;

    virtual void loop() = 0;

private:
    const Args *args;
    AppWindow *appWindow;

    Font *fpsFont;
    FpsCounter fps = FpsCounter();

    double lastFrame = 0;
};


#endif //TILESGE_GAMEAPP_H
