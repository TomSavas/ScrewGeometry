#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"

#include "glm/glm.hpp"

class Texture 
{
public:
    Texture(glm::ivec2 size = glm::ivec2(1), glm::vec2 scale = glm::vec2(1.f));
    Texture(const char *filepath, bool load = false, glm::vec2 scale = glm::vec2(1.f));
    virtual ~Texture();

    virtual bool Load(bool reload = false);

    void Activate(GLenum textureNumber) const;
    void Bind() const;
    void Unbind() const;

    glm::ivec2 Size() const;
    unsigned int Id() const;
    glm::vec2 Scale() const;

    static Texture &DefaultTexture();

protected:
    unsigned int id;
    const char *filepath;
    bool loaded;
    glm::ivec2 size;
    glm::vec2 scale;
};

#endif
