#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

class Shader 
{
private:
    GLenum type;
    unsigned int id;

    const char *filepath;
    char *content;

    bool loaded;
    bool compiled;

    Shader(GLenum shaderType);

public:
    Shader(const char *shaderFilepath, GLenum shaderType, bool load = false, bool compile = false);
    ~Shader();

    static Shader FromSource(const char *shaderSource, GLenum shaderType, bool compile = false);

    bool Load(bool reload = false);
    bool Compile(bool recompile = false);

    unsigned int Id() const;
    bool IsLoaded() const;
    bool IsCompiled() const;
};

#endif
