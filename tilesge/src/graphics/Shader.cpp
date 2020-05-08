#include "graphics/Shader.h"

Shader::Shader(const GLchar *vertexName, const GLchar *fragmentName) {
    this->ID = ShaderLoader::loadShaders(vertexName, fragmentName);
}

void Shader::use() {
    glUseProgram(this->ID);
}

void Shader::attrib(const GLchar *name, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                    const GLvoid *pointer) {
    GLint aPosLocation = glGetAttribLocation(this->ID, name);
    glVertexAttribPointer(aPosLocation, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(aPosLocation);
}

void Shader::set(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
}

void Shader::set(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set(const std::string &name, float first, float second, float third, float forth) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), first, second, third, forth);
}

void Shader::set(const std::string &name, glm::vec3 vec3) {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), vec3.x, vec3.y, vec3.z);
}

void Shader::set(const std::string &name, glm::mat4 matrix) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}
