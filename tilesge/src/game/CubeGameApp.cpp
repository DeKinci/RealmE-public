//
// Created by DeKinci on 4/3/2021.
//

#include "game/CubeGameApp.h"
#include "utils/Log.h"
#include "graphics/Textures.h"

CubeGameApp::CubeGameApp(const Args *args) : GameApp(args) {
    physicsProcessor = new NewtonianPhysicsProcessor(1);

    static int keys[] = {
            GLFW_KEY_1, GLFW_KEY_2, GLFW_KEY_3, GLFW_KEY_4, GLFW_KEY_5, GLFW_KEY_6, GLFW_KEY_7, GLFW_KEY_8, GLFW_KEY_9,
            GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT,
            0
    };
    keyboardManager = new KeyboardManager(keys);
    keyboardManager->bind(GLFW_KEY_1, [this](bool){ physicsProcessor->setPhysSpeed(0, false); });
    keyboardManager->bind(GLFW_KEY_2, [this](bool){ physicsProcessor->setPhysSpeed(1, true); });
    keyboardManager->bind(GLFW_KEY_3, [this](bool){ physicsProcessor->setPhysSpeed(10, true); });
    keyboardManager->bind(GLFW_KEY_4, [this](bool){ physicsProcessor->setPhysSpeed(100, true); });
    keyboardManager->bind(GLFW_KEY_5, [this](bool){ physicsProcessor->setPhysSpeed(1000, true); });
    keyboardManager->bind(GLFW_KEY_6, [this](bool){ physicsProcessor->setPhysSpeed(-1, true); });
    keyboardManager->bind(GLFW_KEY_7, [this](bool){ physicsProcessor->setPhysSpeed(-10, true); });
    keyboardManager->bind(GLFW_KEY_8, [this](bool){ physicsProcessor->setPhysSpeed(-100, true); });
    keyboardManager->bind(GLFW_KEY_9, [this](bool){ physicsProcessor->setPhysSpeed(-1000, true); });


    auto cubes = generateCubeMap();
    gs = new GlobalState(*cubes);
    for (auto c : *cubes) {
        delete c;
    }
    delete cubes;
    light = CubeForge::createLight(0, 50, 0);


    camera->setPos(glm::vec3(18, 8, 18));
    camera->setYaw(-135);
    camera->setPitch(-15);
    Log::info("Game setup complete");
}

void CubeGameApp::loop() {
    physicsProcessor->updatePositions(deltaTime, gs);

    speed = 0;
    static const float defSpeed = 10;

    if (keyboardManager->getIsKeyDown(GLFW_KEY_W)) {
        direction = Direction::FRONT;
        speed = defSpeed;
    }
    if (keyboardManager->getIsKeyDown(GLFW_KEY_S)) {
        direction = Direction::BACK;
        speed = defSpeed;
    }
    if (keyboardManager->getIsKeyDown(GLFW_KEY_A)) {
        direction = Direction::LEFT;
        speed = defSpeed;
    }
    if (keyboardManager->getIsKeyDown(GLFW_KEY_D)) {
        direction = Direction::RIGHT;
        speed = defSpeed;
    }
    if (keyboardManager->getIsKeyDown(GLFW_KEY_SPACE)) {
        direction = Direction::UP;
        speed = defSpeed;
    }
    if (keyboardManager->getIsKeyDown(GLFW_KEY_LEFT_SHIFT)) {
        direction = Direction::DOWN;
        speed = defSpeed;
    }

    if (speed > 0)
        camera->move(direction, speed * deltaTime);

    for (auto cube : gs->getFront().all()) {
        cube->show(*camera);
    }

    light->show(*camera);
    gs->swap();
}

std::vector<Body *> *CubeGameApp::generateCubeMap() {
    auto vector = new std::vector<Body *>;

    auto dogg = CubeForge::createCube(Textures::doggo(), 0, 4, 0, 1);
//    auto dogg = CubeForge::createCube(Textures::doggo(), -5, 10, 1, 1);
    dogg->setPermAcceleration(glm::vec3(0, -10, 0));
    dogg->restitution = .8f;
    vector->push_back(dogg);
//    vector->push_back(CubeForge::createCube(Textures::grass(), 0, 0, 0, 100));

//    for (int i = -10; i < 10; i++)
//        for (int j = -10; j < 10; j++)
//            generateTree(vector, i * 10, 0, j * 10);
    generateTree(vector, 0, 1, 0);
    generateTree(vector, 7, 1, 7);

    for (auto bod : *vector)
        bod->setPermAcceleration(glm::vec3(0, -10, 0));

    for (int i = -10; i < 10; i++)
        for (int j = -10; j < 10; j++)
            vector->push_back(CubeForge::createCube(Textures::grass(), i, 0, j, 100));

    return vector;
}

void CubeGameApp::generateTree(std::vector<Body *> *vector, int x, int y, int z) {
    for (int i = 1; i < 6; i++)
        vector->push_back(CubeForge::createCube(Textures::slab(), x, i, z, 5));

    for (int k = 6; k < 10; k++)
        for (int i = -5; i < 5; i++)
            for (int j = -5; j < 5; j++)
                if (sqrt(i * i + j * j) < 10 - k)
                    vector->push_back(CubeForge::createCube(Textures::leaf(), x + i, k + y, z + j, 0.1));
}

CubeGameApp::~CubeGameApp() {
    delete  keyboardManager;
    delete physicsProcessor;
    delete gs;
    delete light;
}
