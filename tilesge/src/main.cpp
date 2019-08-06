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

static const struct {
    float x, y;
    float r, g, b;
} vertices[3] = {
        {-0.6f, -0.4f, 1.f, 0.f, 0.f},
        {0.6f,  -0.4f, 0.f, 1.f, 0.f},
        {0.f,   0.6f,  0.f, 0.f, 1.f}
};

static const char *vertex_shader_text =
        "#version 110\n"
        "uniform mat4 MVP;\n"
        "attribute vec3 vCol;\n"
        "attribute vec2 vPos;\n"
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
        "    color = vCol;\n"
        "}\n";

static const char *fragment_shader_text =
        "#version 110\n"
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vec4(color, 1.0);\n"
        "}\n";

static void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
};

int main() {
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
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSwapInterval(1);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    Texture *texture = load();
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->u2, texture->v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->image);
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

//    GLuint programID = loadShaders( "vertex.glsl", "color.glsl" );
//    GLint mvp_location = glGetUniformLocation(programID, "MVP");
//    GLint vpos_location = glGetAttribLocation(programID, "vPos");
//    GLint vcol_location = glGetAttribLocation(programID, "vCol");
//    glEnableVertexAttribArray(vpos_location);
//    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void *) nullptr);
//    glEnableVertexAttribArray(vcol_location);
//    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void *) (sizeof(float) * 2));

    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float ratio = (float) width / (float) height;

        mat4x4 m, p, mvp;
        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float) glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
//        glBindTexture(GL_TEXTURE_2D, textureId);

//        glUseProgram(programID);
//        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *) mvp);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}