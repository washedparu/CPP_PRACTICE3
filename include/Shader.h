#pragma once

#include <string>
#include <unordered_map>

struct ShaderPath{
    std::string VertShader;
    std::string FragShader;
};

class Shader
{
private:
    unsigned int m_RendererID;
    std::string m_FragShaderPath;
    std::string m_VertShaderPath;

    unsigned int GetUniformLoc(const std::string& name);
    std::unordered_map<std::string, int> m_UniformLocationCache;
    
    unsigned int CreateShader(const std::string& vertShader, const std::string& fragShader);
    unsigned int CompileShader(const std::string& source, unsigned int type);
    ShaderPath ReadShaderFromFile(const std::string& vertPath, const std::string& fragPath);

public:
    Shader(const std::string& vertShaderPath, const std::string& fragShaderPath);
    ~Shader();


    void Bind() const;
    void UnBind() const;

    void SetUniform1f(const std::string& name, float f1);
    void SetUniform2f(const std::string& name, float f1, float f2);
    void SetUniform3f(const std::string& name, float f1, float f2, float f3);
};