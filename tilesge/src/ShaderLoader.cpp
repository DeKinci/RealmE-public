//
// Created by DeKinci on 8/6/2019.
//

#include "ShaderLoader.h"

CMRC_DECLARE(shaders);

GLuint ShaderLoader::loadShaders(const char *vertexShaderResource, const char *fragmentShaderResource) {
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    auto fs = cmrc::shaders::get_filesystem();

    auto vertexShaderName = std::string(vertexShaderResource) + ".glsl";
    auto vtx = fs.open(vertexShaderName);
    auto VertexShaderCode = std::string(vtx.begin(), vtx.end());

    auto fragmentShaderName = std::string(fragmentShaderResource) + ".glsl";
    auto clr = fs.open(fragmentShaderName);
    auto FragmentShaderCode = std::string(clr.begin(), clr.end());

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    char const *VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    char const *FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Link the program
    GLuint programID = glCreateProgram();
    glAttachShader(programID, VertexShaderID);
    glAttachShader(programID, FragmentShaderID);
    glLinkProgram(programID);

    // Check the program
    glGetProgramiv(programID, GL_LINK_STATUS, &Result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(programID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
    }

    glDetachShader(programID, VertexShaderID);
    glDetachShader(programID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return programID;
}
