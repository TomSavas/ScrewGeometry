#include <assert.h>

#include "renderer/framebuffer.h"

#include "glad/glad.h"

Framebuffer::Framebuffer() 
{
    glGenFramebuffers(1, &id);
}

Framebuffer::~Framebuffer() 
{
    glDeleteFramebuffers(1, &id);
}

void Framebuffer::Bind()
{
    assert(("Atempted to bind incomplete framebuffer", glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE));

    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void Framebuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::CheckComplete()
{
    assert(("Framebuffer is incomplete", glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE));
}

void Framebuffer::SetRenderTexture(Texture *texture)
{
    tex = texture;

    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex->Id(), 0);  
}

void Framebuffer::SetDepthStencilTarget(Renderbuffer *renderbuffer)
{
    rb = renderbuffer;

    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rb->Id());
}

Texture* Framebuffer::Tex()
{
    return tex;
}

Renderbuffer* Framebuffer::Rb()
{
    return rb;
}