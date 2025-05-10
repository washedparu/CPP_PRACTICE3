#pragma once
#include <iostream>

class VertexBuffer
{
private:
    unsigned int m_RendrerID;
public:

    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    VertexBuffer(const VertexBuffer& copy) {
        printf("Copied VertexBuffer\n");
    }
    void Bind() const;
    void unBind() const;
};
