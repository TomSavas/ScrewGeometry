#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "glad/glad.h"

#include "shaders/shader.h"

Shader::Shader(const char *shaderFilepath, GLenum shaderType, bool compile, bool load)
    : Shader(shaderType)
{
    filepath = shaderFilepath;

    if (load)
        Load();
    if (compile)
        Compile();
}

Shader::Shader(GLenum shaderType)
    : type(type), filepath(""), content(nullptr), loaded(false), compiled(false), id(glCreateShader(shaderType))
{
}

Shader::~Shader() 
{
    printf("deleting shader: %s\n", filepath);
    
    if (loaded)
        glDeleteShader(id);

    delete content;
}

/* static */ Shader Shader::FromSource(const char *shaderSource, GLenum shaderType, bool compile) 
{
    Shader shader(shaderType);
    shader.content = (char*) malloc(strlen(shaderSource) + 1);
    strcpy(shader.content, shaderSource);
    shader.loaded = true;

    switch (shaderType) 
    {
        case GL_VERTEX_SHADER:
            shader.filepath = "DEFAULT_VERTEX_SHADER";
            break;
        case GL_FRAGMENT_SHADER:
            shader.filepath = "DEFAULT_FRAGMENT_SHADER";
            break;
        default:
            shader.filepath = "DEFAULT_SHADER";
            break;
    }

    if (compile)
        shader.Compile();

    return shader;
}

bool Shader::Load(bool reload)
{
    if (loaded && !reload)
        return true;

    loaded = false;

    FILE *file = fopen(filepath, "r");

    if (!file) 
    {
        fprintf(stderr, "Shader not found at %s\n", filepath);
        return false;
    }

    fseek(file, 0, SEEK_END);
    // We will need to add a null terminator char
    long size = ftell(file) + 1;
    rewind(file);

    if (!content)
        content = (char*) calloc(size, sizeof(char));
    else
        content = (char*) realloc(content, size * sizeof(char));

    fread(content, sizeof(char), size, file);
    fclose(file);

    if (strlen(content) == 0)
    {
        fprintf(stderr, "Shader file %s was empty\n", filepath);
        return false;
    }

    content[size] = '\0';

    loaded = true;
    return true;
}

bool Shader::Compile(bool recompile)
{
    if (compiled && !recompile)
        return true;

    compiled = false;

    if (!loaded) 
    {
        fprintf(stderr, "Shader must be loaded before compiling it!\n");
        return false;
    }

    glShaderSource(id, 1, &content, NULL);
    glCompileShader(id);

    int compilationSucceeded;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compilationSucceeded);

    if (compilationSucceeded) 
    {
        printf("Compiled %s successfully\n", filepath);
        compiled = true;
        return true;
    }

    int logLength = 0;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);

    char infoLog[logLength];
    glGetShaderInfoLog(id, logLength, NULL, infoLog);
    fprintf(stderr, "Failed to compile shader %s:\n%s\n", filepath, infoLog);

    return false;
}

unsigned int Shader::Id() const 
{
    return id;
}

bool Shader::IsLoaded() const
{
    return loaded;
}

bool Shader::IsCompiled() const
{
    return compiled;
}
