#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "renderer/buffer.h"

class VertexBuffer : public Buffer
{
public:
    VertexBuffer();
    VertexBuffer(float *vertices, int size);
    VertexBuffer(float *vertices, int size, unsigned int id);

    void Bind() const override;
    void Unbind() const override;

    int Size() const override;

private:
    unsigned int id;
    int size;
    bool loaded;
};

#endif
