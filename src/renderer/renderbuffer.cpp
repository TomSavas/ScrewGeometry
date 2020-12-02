#include "renderer/renderbuffer.h"

Renderbuffer::Renderbuffer(glm::ivec2 size, GLenum internalFormat)
{
    glGenRenderbuffers(1, &id);
    glBindRenderbuffer(GL_RENDERBUFFER, id); 
    glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, size.x, size.y);  
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

Renderbuffer::~Renderbuffer()
{
    glDeleteRenderbuffers(1, &id);
}

void Renderbuffer::Bind()
{
    glBindRenderbuffer(GL_RENDERBUFFER, id); 
}

void Renderbuffer::Unbind()
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

glm::ivec2 Renderbuffer::Size() const
{
    return size;
}

unsigned int Renderbuffer::Id() const
{
    return id;
}