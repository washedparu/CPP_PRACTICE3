#include "core.hpp"

namespace Core {
    GLFWwindow* Engine::m_Window = nullptr;
    std::vector<float> vertices;

    // Initialize the application
    bool Engine::Init(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* shared) {
        if (!glfwInit()) {
            ERROR("Failed initializing GLFW.");
            return false;
        }
        INFO("GLFW initialized successfully.");

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        m_Window = glfwCreateWindow(width, height, title, monitor, shared);
        if (!m_Window) {
            glfwTerminate();
            ERROR("Couldn't create window!");
            return false;
        }
        INFO("Created window successfully.");

        glfwMakeContextCurrent(m_Window);

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            ERROR("Couldn't initialize GLEW!");
            glfwDestroyWindow(m_Window);
            glfwTerminate();
            return false;
        }
        INFO("GLEW initialized successfully!");
        return true;
    }

    void Engine::DrawGeometrie() {
        glDrawArrays(GL_QUADS, 0, 4);
    }

    void Engine::Run() {
        if (!m_Window) {
            ERROR("Window is not initialized. Call Core::Init() first.");
            return;
        }

        INFO("GL version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

        vertices.reserve(8);
        vertices.insert(vertices.end(), {
            -0.75f, -0.75f,
             0.75f, -0.75f,
             0.75f,  0.75f,
            -0.75f,  0.75f
        });

        uint32_t quad_buffer;
        glGenBuffers(1, &quad_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, quad_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);  // Unbind buffer

        std::string vertShader = 
            "#version 330 core\n"
            "layout(location = 0) in vec4 position;\n"
            "void main() {\n"
            "    gl_Position = position;\n"
            "}\n";

        std::string fragShader =  
            "#version 330 core\n"
            "layout(location = 0) out vec4 color;\n"
            "void main() {\n"
            "    color = vec4(1.0,0.0,0.0,1.0);\n"
            "}\n";

        unsigned int shader = CreateShader(vertShader, fragShader);
        glUseProgram(shader);

        while (!glfwWindowShouldClose(m_Window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            DrawGeometrie();

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }

        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    Engine::~Engine() {
        if (m_Window) {
            glfwDestroyWindow(m_Window);
            m_Window = nullptr;  // Avoid dangling pointers
        }
        glfwTerminate();
    }

    uint32_t Engine::compileShader(const std::string& source, uint32_t type) {
        uint32_t id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (!result) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

            std::vector<char> message(length);
            glGetShaderInfoLog(id, length, &length, message.data());
            ERROR("Failed to compile {} shader", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
            ERROR("{}", message.data());
            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    uint32_t Engine::CreateShader(const std::string& vertShader, const std::string& fragShader) {
        uint32_t program = glCreateProgram();
        uint32_t vs = compileShader(vertShader, GL_VERTEX_SHADER);
        uint32_t fs = compileShader(fragShader, GL_FRAGMENT_SHADER);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }










    std::vector<double> Math::normalize(std::vector<float> p_values) {
        std::vector<double> normalizedValues;
        for (auto& v : p_values) {
            if (v < 0.0f || v > 255.0f) {
                ERROR("Value out of range: {}. Please provide a value between 0.0 and 255.0", v);
                return {};
            }
            normalizedValues.push_back(v / 255.0);
        }
        return normalizedValues;
    }
}
