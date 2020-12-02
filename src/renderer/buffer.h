#ifndef BUFFER_H
#define BUFFER_H

class Buffer 
{
public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual int Size() const = 0;
};

#endif
