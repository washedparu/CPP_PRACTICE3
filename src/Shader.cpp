#include <Shader.h>

Shader::Shader(const std::string& vertShaderPath, const std::string& fragShaderPath)  
    : m_VertShaderPath(vertShaderPath), m_FragShaderPath(fragShaderPath) ,m_RendererID(0)
{
    ShaderPath src = ReadShaderFromFile(vertShaderPath, fragShaderPath);
    m_RendererID = CreateShader(src.VertShader, src.FragShader);

    GLCall(glUseProgram(m_RendererID));
}

unsigned int Shader::CompileShader(const std::string& source, unsigned int type) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (!result) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

        std::vector<char> message(length);
        GLCall(glGetShaderInfoLog(id, length, &length, message.data()));
        ERROR("Failed to compile {} shader", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
        ERROR("{}", message.data());
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertShader, const std::string& fragShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(vertShader, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragShader, GL_FRAGMENT_SHADER);
    if (!vs || !fs) {
        GLCall(glDeleteProgram(program));
        return 0;
    }

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}


Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}

ShaderPath Shader::ReadShaderFromFile(const std::string& vertPath, const std::string& fragPath) {
    std::ifstream vertFile(vertPath);
    std::ifstream fragFile(fragPath);

    if (!vertFile.is_open()) {
        ERROR("Failed to open vertex shader file: {}", vertPath);
        return {};
    }
    if (!fragFile.is_open()) {
        ERROR("Failed to open fragment shader file: {}", fragPath);
        return {};
    }

    std::stringstream vertBuffer, fragBuffer;
    vertBuffer << vertFile.rdbuf();
    fragBuffer << fragFile.rdbuf();

    return ShaderPath{ vertBuffer.str(), fragBuffer.str() };
}



void Shader::Bind() const {
    GLCall(glUseProgram(m_RendererID));
}

void Shader::UnBind() const {
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1f(const std::string& name, float f1) {
    GLCall(glUniform1f(GetUniformLoc(name), f1));
}


void Shader::SetUniform2f(const std::string& name, float f1, float f2) {
    GLCall(glUniform2f(GetUniformLoc(name), f1, f2));
}


void Shader::SetUniform3f(const std::string& name, float f1, float f2, float f3) {
    GLCall(glUniform3f(GetUniformLoc(name), f1, f2, f3));
}


unsigned int Shader::GetUniformLoc(const std::string& name) {

    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) { 
        return m_UniformLocationCache[name];
    }
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if(location == -1) { 
        ERROR("Couldn't get uniform location\n");
        return -1;
    }
    
    m_UniformLocationCache[name] = location; 
    
    return location;
}