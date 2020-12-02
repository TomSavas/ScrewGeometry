#include <cstdarg>
#include <stdio.h>

#include "glad/glad.h"

#include "shaders/shader_program.h"

ShaderProgram::ShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath)
    : id(glCreateProgram())
{
    Shader vertexShader(vertexShaderPath, GL_VERTEX_SHADER);
    vertexShader.Load();
    vertexShader.Compile();

    Shader fragmentShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    fragmentShader.Load();
    fragmentShader.Compile();

    Link(vertexShader, fragmentShader);
}

ShaderProgram::ShaderProgram(Shader &vertexShader, Shader &fragmentShader)
    : id(glCreateProgram())
{
    Link(vertexShader, fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(id);
}

void ShaderProgram::Use()
{
    glUseProgram(id);
}

void ShaderProgram::SetMVP(const glm::mat4 mvp)
{
    Use();
    SetUniform("mvp", mvp);
}

void ShaderProgram::SetUniform(const char *uniformName, int value)
{
    Use();
    glUniform1i(glGetUniformLocation(id, uniformName), value);   
}

void ShaderProgram::SetUniform(const char *uniformName, float value)
{
    Use();
    glUniform1f(glGetUniformLocation(id, uniformName), value);   
}

void ShaderProgram::SetUniform(const char *uniformName, bool value)
{
    Use();
    glUniform1i(glGetUniformLocation(id, uniformName), value);   
}

void ShaderProgram::SetUniform(const char *uniformName, glm::vec2 value)
{
    Use();
    glUniform2fv(glGetUniformLocation(id, uniformName), 1, glm::value_ptr(value));   
}

void ShaderProgram::SetUniform(const char *uniformName, glm::vec3 value)
{
    Use();
    glUniform3fv(glGetUniformLocation(id, uniformName), 1, glm::value_ptr(value));   
}

void ShaderProgram::SetUniform(const char *uniformName, glm::vec4 value)
{
    Use();
    glUniform4fv(glGetUniformLocation(id, uniformName), 1, glm::value_ptr(value));   
}

void ShaderProgram::SetUniform(const char *uniformName, glm::mat4 value)
{
    Use();
    glUniformMatrix4fv(glGetUniformLocation(id, uniformName), 1, GL_FALSE, glm::value_ptr(value));   
}

/* static */ ShaderProgram &ShaderProgram::DefaultShader()
{
    //static const char *defaultVertShaderCode =
    //    "#version 330 core                              \n"
    //    "                                               \n"
    //    "layout (location = 0) in vec3 pos;             \n"
    //    "layout (location = 1) in vec3 normal;          \n"
    //    "layout (location = 2) in vec2 uv;              \n"
    //    "                                               \n"
    //    "uniform mat4 mvp;                              \n"
    //    "                                               \n"
    //    "out vec4 color;                                \n"
    //    "                                               \n"
    //    "void main()                                    \n"
    //    "{                                              \n"
    //    "   gl_Position = mvp * vec4(pos.xyz, 1.0);     \n"
    //    "   color = vec4(pos.xyz, 1.0);                 \n"
    //    "}                                              \n";
    //static const char *defaultFragShaderCode =
    //    "#version 330 core                              \n"
    //    "                                               \n"
    //    "in vec4 color;                                 \n"
    //    "out vec4 fragColor;                            \n"
    //    "                                               \n"
    //    "void main()                                    \n"
    //    "{                                              \n"
    //    "   fragColor = color;                          \n"
    //    "}                                              \n";

    //static Shader vertShader = Shader::FromSource(defaultVertShaderCode, GL_VERTEX_SHADER, true);
    //static Shader fragShader = Shader::FromSource(defaultFragShaderCode, GL_FRAGMENT_SHADER, true);
    static Shader vertShader ("../src/shaders/default.vert", GL_VERTEX_SHADER, true, true);
    static Shader fragShader ("../src/shaders/default.frag", GL_FRAGMENT_SHADER, true, true);
    static ShaderProgram shader(vertShader, fragShader);

    return shader;
}

void ShaderProgram::Link(Shader &vertexShader, Shader &fragmentShader) 
{
    glAttachShader(id, vertexShader.Id());
    glAttachShader(id, fragmentShader.Id());
    glLinkProgram(id);

    int linkingSucceeded;
    glGetProgramiv(id, GL_LINK_STATUS, &linkingSucceeded);

    if (linkingSucceeded) 
    {
        printf("Linked successfully\n");
        return;
    }

    int logLength = 0;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);

    char infoLog[logLength];
    glGetProgramInfoLog(id, logLength, NULL, infoLog);
    fprintf(stderr, "Failed to link shader:\n%s\n", infoLog);
}
