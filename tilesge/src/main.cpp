#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "linmath.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <lodepng.h>

//static const struct {
//    float x, y;
//    float r, g, b;
//} vertices[3] = {
//        {-0.6f, -0.4f, 1.f, 0.f, 0.f},
//        {0.6f,  -0.4f, 0.f, 1.f, 0.f},
//        {0.f,   0.6f,  0.f, 0.f, 1.f}
//};

float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,   // bottom left
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,    // top right
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // top left
};

unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void error_callback(int error, const char *description);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

GLFWwindow *init() {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(640, 480, "Mah triangle", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSwapInterval(1);
    return window;
}

int main() {
    GLFWwindow *window = init();

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


//    Texture *texture = load();
//    glEnable(GL_TEXTURE_2D);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->u2, texture->v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->image);
//    GLuint textureId;
//    glGenTextures(1, &textureId);
//    glBindTexture(GL_TEXTURE_2D, textureId);

    GLuint programID = loadShaders("vertex.glsl", "color.glsl");
//    GLint mvp_location = glGetUniformLocation(programID, "MVP");
//    GLint vpos_location = glGetAttribLocation(programID, "vPos");
//    GLint vcol_location = glGetAttribLocation(programID, "vCol");
//    glEnableVertexAttribArray(vpos_location);
//    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void *) nullptr);
//    glEnableVertexAttribArray(vcol_location);
//    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void *) (sizeof(float) * 2));

    GLint aPosLocation = glGetAttribLocation(programID, "aPos");
    glVertexAttribPointer(aPosLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(aPosLocation);
    GLint aColorLocation = glGetAttribLocation(programID, "aColor");
    glVertexAttribPointer(aColorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3* sizeof(float)));
    glEnableVertexAttribArray(aColorLocation);

    glBindVertexArray(VertexArrayID);

    while (!glfwWindowShouldClose(window)) {
//        int width, height;
//        glfwGetFramebufferSize(window, &width, &height);
//        float ratio = (float) width / (float) height;
//
//        mat4x4 m, p, mvp;
//        mat4x4_identity(m);
//        mat4x4_rotate_Z(m, m, (float) glfwGetTime());
//        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
//        mat4x4_mul(mvp, p, m);

//        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
//        glBindTexture(GL_TEXTURE_2D, textureId);

//        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *) mvp);
        glUseProgram(programID);

        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(programID, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}
