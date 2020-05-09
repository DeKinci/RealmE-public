//
// Created by DeKinci on 5/9/2020.
//

#include "GameApp.h"

#include "game/CubeForge.h"
#include "graphics/Textures.h"
#include "utils/Log.h"


void doTree(std::vector<Body *> *vector, int x, int y, int z) {
    for (int i = 1; i < 6; i++)
        vector->push_back(CubeForge::createCube(Textures::slab(), x, i, z));

    for (int k = 6; k < 10; k++)
        for (int i = -5; i < 5; i++)
            for (int j = -5; j < 5; j++)
                if (sqrt(i * i + j * j) < 10 - k)
                    vector->push_back(CubeForge::createCube(Textures::leaf(), x + i, k + y, z + j));
}

std::vector<Body *> *doCubes() {
    auto vector = new std::vector<Body *>;

    auto dogg = CubeForge::createCube(Textures::doggo(), -5, 4, 1);
    dogg->setAcceleration(glm::vec3(0, -10, 0));
    vector->push_back(dogg);

    for (int i = -10; i < 10; i++)
        for (int j = -10; j < 10; j++)
            vector->push_back(CubeForge::createCube(Textures::grass(), i, 0, j));

//    for (int i = -10; i < 10; i++)
//        for (int j = -10; j < 10; j++)
//            doTree(vector, i * 10, 0, j * 10);
    doTree(vector, 0, 0, 0);
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
    cubes = doCubes();
    light = CubeForge::createLight(0, 50, 0);

    font = &FontLoader::load("arial");

    camera->setAspectRatio((float) args->getWidth() / (float) args->getHeight());
    camera->setPos(glm::vec3(0, 4, 12));
    camera->setYaw(-90);

//    lastFrame = glfwGetTime();
}

void GameApp::loop() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    Log::debug("frame time {}", deltaTime);
//        glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    physicsProcessor->updatePositions(deltaTime, *cubes);
    for (auto cube : *cubes) {
        cube->show(*camera);
    }

    light->show(*camera);

    fps[fpsPointer] = 1 / deltaTime;
    fpsPointer = ++fpsPointer % fpl;
    double sumFps = 0;
    for (float fp : fps)
        sumFps += fp;
    font->show(appWindow->getProjector(), std::to_string(lround(sumFps / fpl)).c_str(), 10, 10);
    appWindow->update();
}

void GameApp::keyPressed(int key) {
    float cameraSpeed = 75 * deltaTime;
    if (appWindow->getKeyState(GLFW_KEY_W) == GLFW_PRESS)
        camera->move(Direction::FRONT, cameraSpeed);
    if (appWindow->getKeyState(GLFW_KEY_S) == GLFW_PRESS)
        camera->move(Direction::BACK, cameraSpeed);
    if (appWindow->getKeyState(GLFW_KEY_A) == GLFW_PRESS)
        camera->move(Direction::LEFT, cameraSpeed);
    if (appWindow->getKeyState(GLFW_KEY_D) == GLFW_PRESS)
        camera->move(Direction::RIGHT, cameraSpeed);
    if (appWindow->getKeyState(GLFW_KEY_SPACE) == GLFW_PRESS)
        camera->move(Direction::UP, cameraSpeed);
    if (appWindow->getKeyState(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera->move(Direction::DOWN, cameraSpeed);
}

