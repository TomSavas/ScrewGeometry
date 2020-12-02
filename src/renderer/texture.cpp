#include "renderer/texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(glm::ivec2 size, glm::vec2 scale)
    : loaded(false), filepath(""), size(size), scale(scale)
{
    glGenTextures(1, &id);
}

Texture::Texture(const char *filepath, bool load, glm::vec2 scale)
    : Texture(glm::ivec2(), scale)
{
    this->filepath = filepath;

    if (load)
    {
        Load();
        Activate(GL_TEXTURE0);
    }
}

Texture::~Texture()
{
}

bool Texture::Load(bool reload)
{
    if (loaded && !reload)
        return true;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);

    if (filepath != "")
    {
        int _;

        stbi_set_flip_vertically_on_load(true);
        unsigned char *texture = stbi_load(filepath, &size.x, &size.y, &_, 0);

        if (texture == nullptr)
            return false;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(texture);
    }
    else if (!reload)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    loaded = true;

    return true;
}

void Texture::Activate(GLenum textureNumber) const
{
    assert(("Cannot bind an unloaded texture", loaded));

    glActiveTexture(textureNumber);
    Bind();
}

void Texture::Bind() const
{
    assert(("Cannot bind an unloaded texture", loaded));

    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind() const
{
    assert(("Cannot unbind an unloaded texture", loaded));

    glBindTexture(GL_TEXTURE_2D, 0);
}

glm::ivec2 Texture::Size() const
{
    assert(("Non-loaded texture doesn't have a size", loaded));

    return size;
}

unsigned int Texture::Id() const
{
    return id;
}

glm::vec2 Texture::Scale() const
{
    return scale;
}

/* static */ Texture &Texture::DefaultTexture()
{
    static Texture texture ("../assets/textures/default.jpeg", true);

    return texture;
}
