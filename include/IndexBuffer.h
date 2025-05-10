#pragma once
#include <iostream>

class IndexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int *data, unsigned int count);
    ~IndexBuffer();
    IndexBuffer(const IndexBuffer& copy); 
    void Bind() const;
    void unBind() const;

    inline unsigned int GetCount() const;
};


