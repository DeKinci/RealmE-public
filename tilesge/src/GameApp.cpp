//
// Created by DeKinci on 5/9/2020.
//

#include "GameApp.h"

#include <cmath>

#include "game/CubeForge.h"
#include "graphics/Textures.h"
#include "utils/Log.h"


void doTree(std::vector<Body *> *vector, int x, int y, int z) {
    for (int i = 1; i < 6; i++)
        vector->push_back(CubeForge::createCube(Textures::slab(), x, i, z, 5));

    for (int k = 6; k < 10; k++)
        for (int i = -5; i < 5; i++)
            for (int j = -5; j < 5; j++)
                if (sqrt(i * i + j * j) < 10 - k)
                    vector->push_back(CubeForge::createCube(Textures::leaf(), x + i, k + y, z + j, 0.1));
}

std::vector<Body *> *doCubes() {
    auto vector = new std::vector<Body *>;

    auto dogg = CubeForge::createCube(Textures::doggo(), 0, 4, 0, 1);
//    auto dogg = CubeForge::createCube(Textures::doggo(), -5, 10, 1, 1);
    dogg->setPermAcceleration(glm::vec3(0, -10, 0));
    dogg->restitution = .8f;
    vector->push_back(dogg);
    vector->push_back(CubeForge::createCube(Textures::grass(), 0, 0, 0, 100));

//    for (int i = -10; i < 10; i++)
//        for (int j = -10; j < 10; j++)
//            vector->push_back(CubeForge::createCube(Textures::grass(), i, 0, j, 10));

//    for (int i = -10; i < 10; i++)
//        for (int j = -10; j < 10; j++)
//            doTree(vector, i * 10, 0, j * 10);
//    doTree(vector, 0, 0, 0);
//    doTree(vector, 7, 0, 7);

//    for (auto bod : *vector)
//        bod->setAcceleration(glm::vec3(0, -10, 0));
    return vector;
}

GameApp::GameApp(const Args *args) {
    GameApp::args = args;
    Log::init(args->getLogfile(), args->isDebug());
    glfwSetErrorCallback([](int code, const char *ch) { Log::critical("OpenGL error code {} msg {}", code, ch); });
    if (!glfwInit())
        exit(EXIT_FAILURE);

    appWindow = new AppWindow(args->getWidth(), args->getHeight(), args->isDebug());
    appWindow->setKeyPress(std::bind(&GameApp::keyPressed, this, std::placeholders::_1));
    camera = appWindow->getCamera();
    physicsProcessor = new NewtonianPhysicsProcessor(1);

    Log::info("Application complete");
}

void GameApp::run() {
    setup();
    while (!appWindow->readyToClose()) {
        loop();
    }
    delete appWindow;
    glfwTerminate();
}

void GameApp::setup() {
    auto cubes = doCubes();
    gs = new GlobalState(*cubes);
    for (auto c : *cubes) {
        delete c;
    }
    delete cubes;
//    light = CubeForge::createLight(0, 50, 0);

    font = &FontLoader::load("arial");

    camera->setAspectRatio((float) args->getWidth() / (float) args->getHeight());
    camera->setPos(glm::vec3(18, 8, 18));
    camera->setYaw(-135);
    camera->setPitch(-15);

    lastFrame = glfwGetTime();
}

void GameApp::loop() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    Log::debug("frame time {}", deltaTime);
//    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    physicsProcessor->updatePositions(deltaTime, gs);
//    physicsProcessor->updatePositions(deltaTime, *cubes);

    if (speed > 0)
        camera->move(direction, speed * deltaTime);

    for (auto cube : gs->getFront().all()) {
        cube->show(*camera);
    }

//    light->show(*camera);


    font->show(appWindow->getProjector(), std::to_string(std::lround(fps.getFps())).c_str(), 10, 10);
    appWindow->update();
    fps.registerFps(deltaTime);
    gs->swap();
}

void GameApp::keyPressed(int key) {
    if (appWindow->getKeyState(GLFW_KEY_4) == GLFW_PRESS)
        physicsProcessor->setPhysSpeed(0, false);
    if (appWindow->getKeyState(GLFW_KEY_5) == GLFW_PRESS)
        physicsProcessor->setPhysSpeed(1, true);
    if (appWindow->getKeyState(GLFW_KEY_6) == GLFW_PRESS)
        physicsProcessor->setPhysSpeed(10, true);
    if (appWindow->getKeyState(GLFW_KEY_7) == GLFW_PRESS)
        physicsProcessor->setPhysSpeed(100, true);
    if (appWindow->getKeyState(GLFW_KEY_8) == GLFW_PRESS)
        physicsProcessor->setPhysSpeed(1000, true);
    if (appWindow->getKeyState(GLFW_KEY_T) == GLFW_PRESS)
        physicsProcessor->setPhysSpeed(-1, true);
    if (appWindow->getKeyState(GLFW_KEY_Y) == GLFW_PRESS)
        physicsProcessor->setPhysSpeed(-10, true);
    if (appWindow->getKeyState(GLFW_KEY_U) == GLFW_PRESS)
        physicsProcessor->setPhysSpeed(-100, true);
    if (appWindow->getKeyState(GLFW_KEY_I) == GLFW_PRESS)
        physicsProcessor->setPhysSpeed(-1000, true);

    speed = 0;
    static const float defSpeed = 10;

    if (appWindow->getKeyState(GLFW_KEY_W) == GLFW_PRESS) {
        direction = Direction::FRONT;
        speed = defSpeed;
    }
    if (appWindow->getKeyState(GLFW_KEY_S) == GLFW_PRESS) {
        direction = Direction::BACK;
        speed = defSpeed;
    }
    if (appWindow->getKeyState(GLFW_KEY_A) == GLFW_PRESS) {
        direction = Direction::LEFT;
        speed = defSpeed;
    }
    if (appWindow->getKeyState(GLFW_KEY_D) == GLFW_PRESS) {
        direction = Direction::RIGHT;
        speed = defSpeed;
    }
    if (appWindow->getKeyState(GLFW_KEY_SPACE) == GLFW_PRESS) {
        direction = Direction::UP;
        speed = defSpeed;
    }
    if (appWindow->getKeyState(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        direction = Direction::DOWN;
        speed = defSpeed;
    }
}

