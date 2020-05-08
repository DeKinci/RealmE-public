//
// Created by DeKinci on 5/3/2020.
//

#include "AppWindow.h"

AppWindow::AppWindow(Camera &camera, int width, int height) :
        camera(camera),
        width(width),
        height(height),
        lastX(width / 2.0),
        lastY(width / 2.0) {
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

//    glfwSwapInterval(1);
    glfwSwapInterval(0);
}

void AppWindow::keyCallback(int key, int scancode, int action, int mods) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    keyPress(window, key);
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

    camera.changeYaw(xoffset);
    camera.changePitch(yoffset);
}

void AppWindow::scrollCallback(double xoffset, double yoffset) {
    camera.changeFov(-(float) yoffset);
}

void AppWindow::sizeCallback(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;

    glViewport(0, 0, width, height);
    projector = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
    camera.setAspectRatio((float) width / (float) height);
}

void AppWindow::setKeyPress(void (*keyPress)(GLFWwindow *, int)) {
    AppWindow::keyPress = keyPress;
}

bool AppWindow::readyToClose() {
    return glfwWindowShouldClose(window);
}

void AppWindow::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

AppWindow::~AppWindow() {
    glfwDestroyWindow(window);
}

const glm::mat4 &AppWindow::getProjector() const {
    return projector;
}
