//
// Created by DeKinci on 5/9/2020.
//

#include "GameApp.h"

#include <cmath>
#include "utils/Log.h"
#include "graphics/FontLoader.h"

GameApp::GameApp(const Args *args) {
    GameApp::args = args;
    Log::init(args->getLogfile(), args->isDebug());
    glfwSetErrorCallback([](int code, const char *ch) { Log::critical("OpenGL error code {} msg {}", code, ch); });
    if (!glfwInit())
        exit(EXIT_FAILURE);

    appWindow = new AppWindow(args->getWidth(), args->getHeight(), args->isDebug());

    camera = appWindow->getCamera();
    projector = appWindow->getProjector();

    fpsFont = &FontLoader::load("arial");

    Log::info("Application init complete");
}

void GameApp::run() {
    lastFrame = glfwGetTime();

    while (!appWindow->readyToClose()) {
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        Log::debug("frame time {}", deltaTime);
//    glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        loop();

        fpsFont->show(projector, std::to_string(std::lround(fps.getFps())).c_str(), 10, 10);

        appWindow->update();
        fps.registerFps(deltaTime);
    }
    delete appWindow;
    glfwTerminate();
}

GameApp::~GameApp() {
    delete appWindow;
    delete fpsFont;
}

