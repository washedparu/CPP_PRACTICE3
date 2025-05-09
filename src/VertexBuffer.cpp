#include <VertexBuffer.h>
#include <renderer.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    GLCall(glGenBuffers(1, &m_RendrerID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendrerID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1,&m_RendrerID));
}

void VertexBuffer::Bind() {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendrerID));
}
void VertexBuffer::unBind() {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER,0));
}