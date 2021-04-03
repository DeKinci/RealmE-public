//
// Created by DeKinci on 5/3/2020.
//

#include "graphics/AppWindow.h"

#include <utility>
#include <glm/gtc/matrix_transform.hpp>
#include "input/KeyboardManager.h"

AppWindow::AppWindow(size_t width, size_t height, bool debug) :
        camera(new Camera()),
        projector(new Projector()),
        width(width),
        height(height),
        lastX(width / 2.0),
        lastY(width / 2.0) {
    AppWindow::debug = debug;

    projector->updateDimensions(width, height);
    camera->setAspectRatio((float) width / (float) height);

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Mah doggo", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetWindowUserPointer(window, this);

    auto keyCallback = [](GLFWwindow *w, int key, int scanCode, int action, int mods) {
        static_cast<AppWindow *>(glfwGetWindowUserPointer(w))->keyCallback(key, scanCode, action, mods);
    };
    glfwSetKeyCallback(window, keyCallback);

    auto cursorCallback = [](GLFWwindow *w, double xpos, double ypos) {
        static_cast<AppWindow *>(glfwGetWindowUserPointer(w))->cursorCallback(xpos, ypos);
    };
    glfwSetCursorPosCallback(window, cursorCallback);

    auto scrollCallback = [](GLFWwindow *w, double xoffset, double yoffset) {
        static_cast<AppWindow *>(glfwGetWindowUserPointer(w))->scrollCallback(xoffset, yoffset);
    };
    glfwSetScrollCallback(window, scrollCallback);

    auto sizeCallback = [](GLFWwindow *w, int width, int height) {
        static_cast<AppWindow *>(glfwGetWindowUserPointer(w))->sizeCallback(width, height);
    };
    glfwSetFramebufferSizeCallback(window, sizeCallback);

    glfwMakeContextCurrent(window);
    if (!gladLoadGL()) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    glDisable(GL_DITHER);
    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POLYGON_SMOOTH);
    glHint(GL_POINT_SMOOTH, GL_DONT_CARE);
    glHint(GL_LINE_SMOOTH, GL_DONT_CARE);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);

    glfwSwapInterval(0);
}

void AppWindow::keyCallback(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (debug) {
        if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        if (key == GLFW_KEY_F2 && action == GLFW_PRESS)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (key == GLFW_KEY_F3 && action == GLFW_PRESS)
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }

    KeyboardManager::callback(window, key, scancode, action, mods);
}

void AppWindow::cursorCallback(double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera->changeYaw(xoffset);
    camera->changePitch(yoffset);
}

void AppWindow::scrollCallback(double xoffset, double yoffset) {
    camera->changeFov(-(float) yoffset);
}

void AppWindow::sizeCallback(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;

    glViewport(0, 0, width, height);
    projector->updateDimensions(newWidth, newHeight);
    camera->setAspectRatio((float) width / (float) height);
}

bool AppWindow::readyToClose() {
    return glfwWindowShouldClose(window);
}

void AppWindow::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

AppWindow::~AppWindow() {
    delete camera;
    delete projector;

    glfwSetWindowShouldClose(window, GLFW_TRUE);
    glfwDestroyWindow(window);
}

Projector *AppWindow::getProjector() const {
    return projector;
}

int AppWindow::getKeyState(int key) {
    return glfwGetKey(window, key);
}

Camera *AppWindow::getCamera() const {
    return camera;
}
