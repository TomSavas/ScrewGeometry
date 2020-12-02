#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "renderer/buffer.h"

class IndexBuffer : public Buffer
{
public:
    IndexBuffer();
    IndexBuffer(unsigned int *indices, int size);
    IndexBuffer(unsigned int *indices, int size, unsigned int id);

    void Bind() const override;
    void Unbind() const override;

    int Size() const override;

private:
    unsigned int id;
    int size;
    bool loaded;
};

#endif
