#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "linmath.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"
#include "Shader.h"
#include "Texture.h"
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <lodepng.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Camera.h"
#include "Model.h"
#include "Mesh.h"
#include "CubeForge.h"
#include "Textures.h"
#include "Body.h"
#include "FontLoader.h"
#include "AppWindow.h"

Camera camera;
AppWindow *window;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

const int WIDTH = 640, HEIGHT = 480;
float lastX = WIDTH / 2.0, lastY = HEIGHT / 2.0;
bool firstMouse = true;

void error_callback(int error, const char *description);

void keyPressed(GLFWwindow *window, int key);

void init() {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = new AppWindow(camera, WIDTH, HEIGHT);
    window->setKeyPress(keyPressed);
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

    for (int i = -20; i < 20; i++)
        for (int j = -20; j < 20; j++)
            vector->push_back(CubeForge::createCube(Textures::grass(), i, 0, j));

    doTree(vector, 0, 0, 0);
    doTree(vector, 7, 0, 7);

    return *vector;
}

float koe = 1.0;
float collY = 1;
int collC = 0;

void animate(std::vector<Body *> &vector) {
    Body &bod = *vector[0];
    auto pos = bod.getPosition();
    auto vel = bod.getVelocity();
    auto acc = bod.getAcceleration();
    float dt = deltaTime;

    if (abs(pos.y - collY) < 0.001 && vel.y < 0.001)
        return;

    float dSpeed = acc.y * deltaTime;
    float nextY = pos.y + vel.y * deltaTime + dSpeed * deltaTime;

    if (nextY <= collY) {
        collC++;
        float fix = (1 - nextY) * acc.y / vel.y;
        if (abs(vel.y) < abs(fix)) {
            fix = -vel.y;
        }
        vel.y += fix;
//        std::cout << ++collC << " " << nextY << " " << fix << " ";
//        std::cout << ++collC << " " << nextY << " ";

        nextY = 2 * collY - nextY;
//        std::cout << nextY << " " << vel.y;
        vel.y += dSpeed;
        vel.y = -vel.y * koe;
//        std::cout << std::endl;
    } else {
        vel.y += dSpeed;
    }

    bod.setPosition(glm::vec3(pos.x, nextY, pos.z));
    bod.setVelocity(vel);
}

int main() {
    camera.setAspectRatio((float) WIDTH / (float) HEIGHT);
    camera.setPos(glm::vec3(0, 4, 12));
    camera.setYaw(-90);

    init();
    std::vector<Body *> &cubes = doCubes();
    Model *light = CubeForge::createLight(0, 50, 0);

    Font &font = FontLoader::load("arial");

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float currentFrame = glfwGetTime();
    lastFrame = currentFrame;

    while (!window->readyToClose()) {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
//        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        font.show(camera, "firchik", 0, 0, VAO, VBO);

        animate(cubes);
        for (auto cube : cubes) {
            cube->show(camera);
        }

        light->show(camera);

        window->update();
    }

    delete window;

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

void keyPressed(GLFWwindow *window, int key) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
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
