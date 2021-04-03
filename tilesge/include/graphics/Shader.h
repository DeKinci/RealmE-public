#ifndef TILESGE_SHADER_H
#define TILESGE_SHADER_H

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Shader {
public:
    GLuint ID;

    Shader(const char *vertexName, const char *fragmentName);

    void use();

    void attrib(const GLchar *name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);

    void set(const GLchar *name, GLboolean value) const;

    void set(const GLchar *name, GLint value) const;

    void set(const GLchar *name, GLfloat value) const;

    void set(const GLchar *name, GLfloat first, GLfloat second, GLfloat third, GLfloat forth) const;

    void set(const GLchar *name, glm::vec3 vec3) const;

    void set(const GLchar *name, glm::mat4) const;

private:
    static GLuint lastUsedGLId;
};


#endif //TILESGE_SHADER_H
