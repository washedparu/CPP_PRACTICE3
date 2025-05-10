#pragma once
#include <renderer.h>
#include <vector>

struct vbe {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getTypeSize(unsigned int t) {
        switch (t) {
            case GL_FLOAT: return sizeof(GLfloat);
            case GL_UNSIGNED_INT: return sizeof(GLuint);
            case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
        }
        ASSERT(false);
        return 0;
    }
};

class BufferLayout {
private:
    int m_Stride = 0;
    std::vector<vbe> m_Elements;
public:
    BufferLayout() = default;

    template<typename T>
    void push(int count);

    const std::vector<vbe>& GetElements() const { return m_Elements; }
    int GetStride() const { return m_Stride; }
};

template<>
inline void BufferLayout::push<float>(int count) {
    m_Elements.push_back({GL_FLOAT, static_cast<unsigned int>(count), false});
    m_Stride += vbe::getTypeSize(GL_FLOAT);
}

template<>
inline void BufferLayout::push<unsigned int>(int count) {
    m_Elements.push_back({GL_UNSIGNED_INT, static_cast<unsigned int>(count), GL_FALSE});
    m_Stride += vbe::getTypeSize(GL_UNSIGNED_INT);
}

template<>
inline void BufferLayout::push<unsigned char>(int count) {
    m_Elements.push_back({GL_UNSIGNED_BYTE, static_cast<unsigned int>(count), GL_TRUE});
    m_Stride += vbe::getTypeSize(GL_UNSIGNED_BYTE);
}