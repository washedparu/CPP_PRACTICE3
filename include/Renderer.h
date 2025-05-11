#pragma once

// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Macros.h>

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

#include <VertexArray.h>
#include <IndexBuffer.h>
#include <Shader.h>


class Renderer
{
private:
public:
    Renderer(); 
    ~Renderer();
    
    void DrawElements(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};

