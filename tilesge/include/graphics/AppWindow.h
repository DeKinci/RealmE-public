//
// Created by DeKinci on 5/3/2020.
//

#ifndef TILESGE_APPWINDOW_H
#define TILESGE_APPWINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <cstdlib>
#include <glm/glm.hpp>
#include "graphics/Camera.h"

class AppWindow {
public:
    AppWindow(Camera *camera, size_t width, size_t height, bool debug);

    virtual ~AppWindow();

    void setKeyPress(std::function<void(int)> callback);

    bool readyToClose();

    void update();

    int getKeyState(int key);

    const glm::mat4 &getProjector() const;

private:
    int width;
    int height;
    bool debug;
    float lastX;
    float lastY;
    bool firstMouse = true;
    GLFWwindow *window;
    Camera *camera;
    glm::mat4 projector;

//    void (*keyPress)(GLFWwindow *, int);
    std::function<void(int)> keyPress;

    void keyCallback(int key, int scancode, int action, int mods);

    void cursorCallback(double xpos, double ypos);

    void scrollCallback(double xoffset, double yoffset);

    void sizeCallback(int width, int height);
};


#endif //TILESGE_APPWINDOW_H
