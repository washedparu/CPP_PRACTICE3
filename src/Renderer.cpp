#include <Renderer.h>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): "
                  << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

Renderer::Renderer() {}
Renderer::~Renderer() {}
void Renderer::DrawElements(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    va.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(),GL_UNSIGNED_INT, nullptr);
}