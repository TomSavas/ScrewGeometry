#include "components/model.h"

Model::Model(objl::Mesh &mesh, Texture &texture)
    : mesh(mesh), texture(texture)
{
    int vertexEntryCount = mesh.Vertices.size() * (3 + 3 + 2);
    float convertedVertices[vertexEntryCount];

    for (int i = 0; i < mesh.Vertices.size(); i++)
    {
        int index = i * (3 + 3 + 2);

        convertedVertices[index + 0] = mesh.Vertices[i].Position.X;
        convertedVertices[index + 1] = mesh.Vertices[i].Position.Y;
        convertedVertices[index + 2] = mesh.Vertices[i].Position.Z;

        convertedVertices[index + 3] = mesh.Vertices[i].Normal.X;
        convertedVertices[index + 4] = mesh.Vertices[i].Normal.Y;
        convertedVertices[index + 5] = mesh.Vertices[i].Normal.Z;

        convertedVertices[index + 6] = mesh.Vertices[i].TextureCoordinate.X;
        convertedVertices[index + 7] = mesh.Vertices[i].TextureCoordinate.Y;
    }

    vertexArray = VertexArray(VertexBuffer(convertedVertices, vertexEntryCount),
        IndexBuffer(&mesh.Indices[0], mesh.Indices.size()),
        BufferLayout({
            { "pos", 3, GL_FLOAT, sizeof(float) },
            { "normal", 3, GL_FLOAT, sizeof(float) },
            { "uv", 2, GL_FLOAT, sizeof(float) },
        })
    );
    vertexArray.Bind();
    texture.Activate(GL_TEXTURE0);
}

/*static*/ Model Model::Quad(glm::vec3 scale, Texture &texture)
{
    static std::vector<unsigned int> indices = { 0, 3, 2, 0, 2, 1 };

    std::vector<objl::Vertex> vertices = { 
        { objl::Vector3(-scale.x / 2.0, -scale.y / 2.0, 0.f), objl::Vector3(0.f, 0.f, 1.f), objl::Vector2(0.f, 0.f) }, // front bot left
        { objl::Vector3(-scale.x / 2.0,  scale.y / 2.0, 0.f), objl::Vector3(0.f, 0.f, 1.f), objl::Vector2(0.f, 1.f) }, // front top left
        { objl::Vector3( scale.x / 2.0,  scale.y / 2.0, 0.f), objl::Vector3(0.f, 0.f, 1.f), objl::Vector2(1.f, 1.f) }, // front top right
        { objl::Vector3( scale.x / 2.0, -scale.y / 2.0, 0.f), objl::Vector3(0.f, 0.f, 1.f), objl::Vector2(1.f, 0.f) }, // front bot right
    };
    objl::Mesh *mesh = new objl::Mesh(vertices, indices);   

    return Model(*mesh, texture);
}

/*static*/ Model Model::DoubleSidedQuad(glm::vec3 scale, Texture &texture)
{
    static std::vector<unsigned int> indices = { 
        0, 3, 2, 0, 2, 1,
        6, 7, 4, 5, 6, 4, // backside due to back face culling
    };

    std::vector<objl::Vertex> vertices = { 
        { objl::Vector3(-scale.x / 2.0, -scale.y / 2.0, 0.f), objl::Vector3(0.f, 0.f, 1.f), objl::Vector2(0.f, 0.f) }, // front bot left
        { objl::Vector3(-scale.x / 2.0,  scale.y / 2.0, 0.f), objl::Vector3(0.f, 0.f, 1.f), objl::Vector2(0.f, 1.f) }, // front top left
        { objl::Vector3( scale.x / 2.0,  scale.y / 2.0, 0.f), objl::Vector3(0.f, 0.f, 1.f), objl::Vector2(1.f, 1.f) }, // front top right
        { objl::Vector3( scale.x / 2.0, -scale.y / 2.0, 0.f), objl::Vector3(0.f, 0.f, 1.f), objl::Vector2(1.f, 0.f) }, // front bot right

        // We need separate vertices with correct normals for back side of the quad
        { objl::Vector3(-scale.x / 2.0, -scale.y / 2.0, 0.f), objl::Vector3(0.f, 0.f, -1.f), objl::Vector2(0.f, 0.f) }, // back bot left
        { objl::Vector3(-scale.x / 2.0,  scale.y / 2.0, 0.f), objl::Vector3(0.f, 0.f, -1.f), objl::Vector2(0.f, 1.f) }, // back top left
        { objl::Vector3( scale.x / 2.0,  scale.y / 2.0, 0.f), objl::Vector3(0.f, 0.f, -1.f), objl::Vector2(1.f, 1.f) }, // back top right
        { objl::Vector3( scale.x / 2.0, -scale.y / 2.0, 0.f), objl::Vector3(0.f, 0.f, -1.f), objl::Vector2(1.f, 0.f) }, // back bot right
    };
    objl::Mesh *mesh = new objl::Mesh(vertices, indices);   

    return Model(*mesh, texture);
}

const objl::Mesh &Model::Mesh() const
{
    return mesh;
}

const Texture &Model::Tex() const
{
    return texture;
}

const VertexArray& Model::VAO() const
{
    return vertexArray;
}

std::string Model::DebugString(std::string linePrefix) const 
{
    return linePrefix + std::string("Mesh name: ") + mesh.MeshName;
}
