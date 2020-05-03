//
// Created by DeKinci on 5/3/2020.
//

#ifndef FREETYPE_APPWINDOW_H
#define FREETYPE_APPWINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include "Camera.h"

class AppWindow {
public:
    AppWindow(Camera &camera, int width, int height);

    virtual ~AppWindow();

    void setKeyPress(void (*keyPress)(GLFWwindow *, int));

    bool readyToClose();

    void update();

private:
    int width;
    int height;
    float lastX;
    float lastY;
    bool firstMouse = true;
    GLFWwindow *window;
    Camera &camera;

    void (*keyPress)(GLFWwindow *, int);

    void keyCallback(int key, int scancode, int action, int mods);

    void cursorCallback(double xpos, double ypos);

    void scrollCallback(double xoffset, double yoffset);

    void sizeCallback(int width, int height);
};


#endif //FREETYPE_APPWINDOW_H
