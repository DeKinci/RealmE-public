//
// Created by DeKinci on 4/3/2021.
//

#include "input/KeyboardManager.h"
#include <algorithm>
#include <utility>

std::vector<KeyboardManager *> KeyboardManager::_instances;

KeyboardManager::KeyboardManager(const int *keysToMonitor) : _isEnabled(true) {
    int key = *keysToMonitor;
    while (key != 0) {
        _keys[key] = false;
        key = *(keysToMonitor++);
    }
    KeyboardManager::_instances.push_back(this);
}

KeyboardManager::~KeyboardManager() {
    _instances.erase(std::remove(_instances.begin(), _instances.end(), this), _instances.end());
}


bool KeyboardManager::getIsKeyDown(int key) {
    bool result = false;
    if (_isEnabled) {
        auto it = _keys.find(key);
        if (it != _keys.end()) {
            result = _keys[key];
        }
    }
    return result;
}

void KeyboardManager::bind(int key, std::function<void(bool)> callback) {
    bindings[key] = std::move(callback);
}

void KeyboardManager::updateKey(int key, bool isDown) {
    auto it = _keys.find(key);
    if (it != _keys.end()) {
        _keys[key] = isDown;
    }

    auto binding = bindings.find(key);
    if (binding != bindings.end()) {
        binding->second(isDown);
    }
}

void KeyboardManager::setupKeyInputs(GLFWwindow *window) {
    glfwSetKeyCallback(window, KeyboardManager::callback);
}

void KeyboardManager::callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_RELEASE) {
        for (KeyboardManager *keyboardManager : _instances) {
            keyboardManager->updateKey(key, action == GLFW_PRESS);
        }
    }
}
