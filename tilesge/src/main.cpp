#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "linmath.h"
#include "Shader.h"
#include "Texture.h"
#include <cstdlib>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CLI11.hpp"
#include <string>
#include "Camera.h"
#include "Model.h"
#include "CubeForge.h"
#include "Textures.h"
#include "Body.h"
#include "FontLoader.h"
#include "AppWindow.h"
#include "ThreadPool.h"
#include "NewtonianPhysicsProcessor.h"
#include "Log.h"
#include "Args.h"


Camera camera;
AppWindow *window;
NewtonianPhysicsProcessor physicsProcessor(30);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

const int WIDTH = 640, HEIGHT = 480;

void keyPressed(GLFWwindow *window, int key);

void init() {
//    Log::init("../../../logs/log.log", true);

    glfwSetErrorCallback([](int code, const char *ch) { Log::critical("OpenGL error code {} msg {}", code, ch); });
    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = new AppWindow(camera, WIDTH, HEIGHT);
    window->setKeyPress(keyPressed);
    Log::info("Initialization complete");
}

void doTree(std::vector<Body *> *vector, int x, int y, int z) {
    for (int i = 1; i < 6; i++)
        vector->push_back(CubeForge::createCube(Textures::slab(), x, i, z));

    for (int k = 6; k < 10; k++)
        for (int i = -5; i < 5; i++)
            for (int j = -5; j < 5; j++)
                if (sqrt(i * i + j * j) < 10 - k)
                    vector->push_back(CubeForge::createCube(Textures::leaf(), x + i, k + y, z + j));
}

std::vector<Body *> &doCubes() {
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
    return *vector;
}

int main(int argc, char **argv) {
    Args args(argc, argv);
    Log::init(args.getLogfile(), args.isDebug());

    camera.setAspectRatio((float) WIDTH / (float) HEIGHT);
    camera.setPos(glm::vec3(0, 4, 12));
    camera.setYaw(-90);

    init();
    std::vector<Body *> &cubes = doCubes();
    Model *light = CubeForge::createLight(0, 50, 0);

    Font &font = FontLoader::load("arial");

//    lastFrame = glfwGetTime();
    const int fpl = 600;
    float fps[fpl] = {};
    int fpsPointer = 0;

    while (!window->readyToClose()) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        Log::debug("frame time {}", deltaTime);
//        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        physicsProcessor.updatePositions(deltaTime, cubes);
        for (auto cube : cubes) {
            cube->show(camera);
        }

        light->show(camera);

        fps[fpsPointer] = 1 / deltaTime;
        fpsPointer = ++fpsPointer % fpl;
        double sumFps = 0;
        for (float fp : fps)
            sumFps += fp;
        font.show(*window, std::to_string(lround(sumFps / fpl)), 10, 10);
        window->update();
    }

    delete window;

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void keyPressed(GLFWwindow *window, int key) {
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

    float cameraSpeed = 7.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.move(Direction::FRONT, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.move(Direction::BACK, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.move(Direction::LEFT, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.move(Direction::RIGHT, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.move(Direction::UP, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.move(Direction::DOWN, cameraSpeed);
}
