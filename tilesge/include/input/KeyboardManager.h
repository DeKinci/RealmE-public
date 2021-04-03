//
// Created by DeKinci on 4/3/2021.
//

#ifndef TILESGE_KEYBOARDMANAGER_H
#define TILESGE_KEYBOARDMANAGER_H

#include <GLFW/glfw3.h>
#include <map>
#include <vector>
#include <functional>

class KeyboardManager {
public:
    explicit KeyboardManager(const int *keysToMonitor);

    ~KeyboardManager();

    bool getIsKeyDown(int key);

    bool getIsEnabled() const { return _isEnabled; }

    void setIsEnabled(bool value) { _isEnabled = value; }

    void bind(int key, std::function<void(bool)> callback);

private:
    void updateKey(int key, bool isDown);

    std::map<int, bool> _keys;
    std::map<int, std::function<void(bool)>> bindings;
    bool _isEnabled;

public:
    static void setupKeyInputs(GLFWwindow *window);
    static void callback(GLFWwindow *window, int key, int scancode, int action, int mods);
private:

    static std::vector<KeyboardManager *> _instances;

};


#endif //TILESGE_KEYBOARDMANAGER_H
