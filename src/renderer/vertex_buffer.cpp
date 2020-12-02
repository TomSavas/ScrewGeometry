#include <cassert>

#include "glad/glad.h"

#include "renderer/vertex_buffer.h"

VertexBuffer::VertexBuffer() 
    : size(0), loaded(false)
{
}

VertexBuffer::VertexBuffer(float *vertices, int size)
    : size(size), loaded(true)
{
    glGenBuffers(1, &id);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(float *vertices, int size, unsigned int id)
    : id(id), size(size), loaded(true)
{
    Bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, vertices, GL_STATIC_DRAW);
}


void VertexBuffer::Bind() const
{
    assert(("Vertex buffer is not loaded", loaded));

    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::Unbind() const
{
    assert(("Vertex buffer is not loaded", loaded));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int VertexBuffer::Size() const
{
    return size;
}
