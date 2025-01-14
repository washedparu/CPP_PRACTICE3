#include <core.hpp>

namespace Core {
    // Static member definition
    GLFWwindow* Engine::m_Window = nullptr;

    std::string ReadFile(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            ERROR("Failed to open file: {}", filePath);
            return "";
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    bool Engine::Init(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* shared) {
        if (!glfwInit()) {
            ERROR("Failed to initialize GLFW.");
            return false;
        }

        m_Window = glfwCreateWindow(width, height, title, monitor, shared);
        if (!m_Window) {
            ERROR("Failed to create GLFW window.");
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(m_Window);
        if (glewInit() != GLEW_OK) {
            ERROR("Failed to initialize GLEW.");
            return false;
        }

        INFO("GLFW and GLEW initialized successfully.");
        return true;
    }

    void Engine::Run() {
        if (!m_Window) {
            ERROR("Window is not initialized. Call Core::Init() first.");
            return;
        }

        INFO("GL version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

        static std::vector<float> vertices = {
            -0.75f, -0.75f,
             0.75f, -0.75f,
             0.75f,  0.75f,
            -0.75f,  0.75f
        };

        uint32_t quad_buffer;
        glGenBuffers(1, &quad_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, quad_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);
        glEnableVertexAttribArray(0);

        std::string vertShader = ReadFile("../res/shaders/vert.glsl");
        std::string fragShader = ReadFile("../res/shaders/frag.glsl");

        if (vertShader.empty() || fragShader.empty()) {
            ERROR("Failed to load shaders. Exiting application.");
            return;
        }

        unsigned int shader = CreateShader(vertShader, fragShader);
        glUseProgram(shader);

        int timeLocation = glGetUniformLocation(shader, "time");

        while (!glfwWindowShouldClose(m_Window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            float timeValue = static_cast<float>(glfwGetTime());
            glUniform1f(timeLocation, timeValue);

            DrawGeometrie();

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }

        glDeleteBuffers(1, &quad_buffer);
        glDeleteProgram(shader);

        if (m_Window) {
            glfwDestroyWindow(m_Window);
            m_Window = nullptr;
        }
        glfwTerminate();
    }

    void Engine::DrawGeometrie() {
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
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
            CRITIC("Failed to compile {} shader:\n{}", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), message.data());
            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    uint32_t Engine::CreateShader(const std::string& vertShader, const std::string& fragShader) {
        uint32_t program = glCreateProgram();
        uint32_t vs = compileShader(vertShader, GL_VERTEX_SHADER);
        uint32_t fs = compileShader(fragShader, GL_FRAGMENT_SHADER);

        if (!vs || !fs) {
            ERROR("Shader creation failed. Aborting.");
            return 0;
        }

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    Engine::~Engine() {
        if (m_Window) {
            glfwDestroyWindow(m_Window);
        }
        glfwTerminate();
        INFO("Engine resources cleaned up.");
    }
}
