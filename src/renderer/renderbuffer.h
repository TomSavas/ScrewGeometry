#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include "glad/glad.h"

#include "glm/glm.hpp"

class Renderbuffer
{
public:
    Renderbuffer(glm::ivec2 size, GLenum internalFormat);
    ~Renderbuffer();

    void Bind();
    void Unbind();

    glm::ivec2 Size() const;
    unsigned int Id() const;

private:
    unsigned int id;

    glm::ivec2 size;
    GLenum internalFormat;
};

#endif