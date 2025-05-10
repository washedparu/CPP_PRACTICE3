#pragma once
#include <VertexBuffer.h>
#include <BufferLayout.h>


class VertexArray
{
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();
    void addBuffer(const VertexBuffer& vb, const BufferLayout& layout);

    void Bind() const;
    void unBind() const;
};

