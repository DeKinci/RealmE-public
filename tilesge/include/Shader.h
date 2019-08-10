#ifndef TILESGE_SHADER_H
#define TILESGE_SHADER_H

#include <glad/glad.h> 
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderLoader.h"

class Shader
{
public:
    // the program ID
    GLuint ID;

    // constructor reads and builds the shader
    Shader(const GLchar* vertexName, const GLchar* fragmentName);
    // use/activate the shader
    void use();
    // f
    void attrib(const GLchar* name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);
    // utility uniform functions
    void set(const std::string &name, bool value) const;
    void set(const std::string &name, int value) const;
    void set(const std::string &name, float value) const;
    void set(const std::string &name, float first, float second, float third, float forth) const;
    void set(const std::string &name, glm::mat4);
};


#endif //TILESGE_SHADER_H
