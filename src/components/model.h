#ifndef MODEL_H
#define MODEL_H

#include "OBJ_Loader.h"

#include "components/icomponent.h"
#include "renderer/texture.h"
#include "renderer/vertex_array.h"

class Model
    : public IComponent
{
public:
    Model(objl::Mesh &mesh, Texture &texture = Texture::DefaultTexture());

    static Model Quad(glm::vec3 scale = glm::vec3(1.0), Texture &texture = Texture::DefaultTexture());
    static Model DoubleSidedQuad(glm::vec3 scale = glm::vec3(1.0), Texture &texture = Texture::DefaultTexture());

    const objl::Mesh &Mesh() const;
    const Texture &Tex() const;
    const VertexArray &VAO() const;

    virtual std::string DebugString(std::string linePrefix = std::string("")) const override;

private:
    objl::Mesh &mesh;
    Texture &texture;
    VertexArray vertexArray;
};

#endif
