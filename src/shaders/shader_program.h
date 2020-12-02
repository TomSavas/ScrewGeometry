#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "glm/gtc/type_ptr.hpp"

#include "shaders/shader.h"

class ShaderProgram 
{
public:
    ShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath);
    ShaderProgram(Shader &vertexShader, Shader &fragmentShader);
    ~ShaderProgram();

    void Use();

    void SetMVP(const glm::mat4 mvp);

    void SetUniform(const char *uniformName, int value);
    void SetUniform(const char *uniformName, float value);
    void SetUniform(const char *uniformName, bool value);
    void SetUniform(const char *uniformName, glm::vec2 value);
    void SetUniform(const char *uniformName, glm::vec3 value);
    void SetUniform(const char *uniformName, glm::vec4 value);
    void SetUniform(const char *uniformName, glm::mat4 value);

    static ShaderProgram &DefaultShader();

private:
    unsigned int id;

    void Link(Shader &vertexShader, Shader &fragmentShader);
};

#endif
