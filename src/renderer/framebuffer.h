#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "renderer/texture.h"
#include "renderer/renderbuffer.h"

#include "components/icomponent.h"

class Framebuffer 
// temporary
    : public IComponent
{
public:
    Framebuffer();
    ~Framebuffer();

    void Bind();
    void Unbind();

    void CheckComplete();

    void SetRenderTexture(Texture *texture);
    void SetDepthStencilTarget(Renderbuffer *renderbuffer);

    Texture* Tex();
    Renderbuffer* Rb();

    unsigned int id;

private:
    Texture* tex;
    Renderbuffer* rb;
};

#endif 