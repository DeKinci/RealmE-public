//
// Created by DeKinci on 5/3/2020.
//

#ifndef TILESGE_APPWINDOW_H
#define TILESGE_APPWINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "graphics/Camera.h"
#include "graphics/Projector.h"

class AppWindow {
public:
    AppWindow(size_t width, size_t height, bool debug);

    virtual ~AppWindow();

    bool readyToClose();

    void update();

    int getKeyState(int key);

    Camera *getCamera() const;

    Projector *getProjector() const;
private:
    int width;
    int height;
    bool debug;
    float lastX;
    float lastY;
    bool firstMouse = true;
    GLFWwindow *window;
    Camera *camera;
    Projector *projector;

    void keyCallback(int key, int scancode, int action, int mods);

    void cursorCallback(double xpos, double ypos);

    void scrollCallback(double xoffset, double yoffset);

    void sizeCallback(int width, int height);
};

#endif //TILESGE_APPWINDOW_H
