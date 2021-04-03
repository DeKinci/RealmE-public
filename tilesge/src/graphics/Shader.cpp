#include "graphics/Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include "graphics/ShaderLoader.h"

GLuint Shader::lastUsedGLId = 0;

Shader::Shader(const char *vertexName, const char *fragmentName) {
    this->ID = ShaderLoader::loadShaders(vertexName, fragmentName);
}

void Shader::use() {
    if (lastUsedGLId != Shader::ID) {
        glUseProgram(Shader::ID);
        lastUsedGLId = Shader::ID;
    }
}

void Shader::attrib(const GLchar *name, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                    const GLvoid *pointer) {
    GLint aPosLocation = glGetAttribLocation(this->ID, name);
    glVertexAttribPointer(aPosLocation, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(aPosLocation);
}

void Shader::set(const GLchar *name, GLboolean value) const {
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::set(const GLchar *name, GLint value) const {
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::set(const GLchar *name, GLfloat value) const {
    glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::set(const GLchar *name, GLfloat first, GLfloat second, GLfloat third, GLfloat forth) const {
    glUniform4f(glGetUniformLocation(ID, name), first, second, third, forth);
}

void Shader::set(const GLchar *name, glm::vec3 vec3) const {
    glUniform3f(glGetUniformLocation(ID, name), vec3.x, vec3.y, vec3.z);
}

void Shader::set(const GLchar *name, glm::mat4 matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}
