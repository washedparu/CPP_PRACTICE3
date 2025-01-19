#include <core.hpp>

namespace Core {
    GLFWwindow* Engine::window = nullptr;
    std::vector<float> vertices;
    std::vector<int> indices;

    // Clear all OpenGL errors
    void Engine::ClearError() {
        while (glGetError() != GL_NO_ERROR);
    }


    std::string Engine::ReadShaderFile(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            ERROR("Failed to open shader file: {}", filePath);
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    struct S {
        std::string vertShader = Engine::ReadShaderFile("../res/shaders/vert.glsl");
        std::string fragShader = Engine::ReadShaderFile("../res/shaders/frag.glsl");
    } typedef Shaders;

    // Initialize the application
    bool Engine::Init(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* shared) {
        if (!glfwInit()) {
            ERROR("Failed initializing GLFW.");
            return false;
        }
        INFO("GLFW initialized successfully.");

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        window = glfwCreateWindow(width, height, title, monitor, shared);
        if (!window) {
            glfwTerminate();
            ERROR("Couldn't create window!");
            return false;
        }
        INFO("Created window successfully.");

        glfwMakeContextCurrent(window);

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            ERROR("Couldn't initialize GLEW!");
            glfwDestroyWindow(window);
            glfwTerminate();
            return false;
        }
        INFO("GLEW initialized successfully!");
        return true;
    }

    void Engine::DrawGeometrie() {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void Engine::Run() {
        Shaders shaders;
        if (!window) {
            ERROR("Window is not initialized. Call Core::Init() first.");
            return;
        }

        INFO("GL version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

        // Define vertices and indices
        vertices = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f
        };

        indices = { 0, 1, 2, 2, 3, 0 };

        // Create Vertex Buffer Object (VBO)
        uint32_t vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        // Create Vertex Array Object (VAO)
        uint32_t vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);
        glEnableVertexAttribArray(0);

        // Create Index Buffer Object (IBO)
        uint32_t ibo;
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);

        // Check and load shaders
        if (shaders.vertShader.empty() || shaders.fragShader.empty()) {
            ERROR("Failed to load shaders. Exiting application.");
            return;
        }

        unsigned int shader = CreateShader(shaders.vertShader, shaders.fragShader);
        glUseProgram(shader);

        int timeLocation = glGetUniformLocation(shader, "time");

        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            
            // Update time uniform
            float timeValue = static_cast<float>(glfwGetTime());
            glUniform1f(timeLocation, timeValue);

            // Draw the geometry
            DrawGeometrie();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // Cleanup
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ibo);
        glDeleteVertexArrays(1, &vao);
        glDeleteProgram(shader);
        glfwDestroyWindow(window);
        glfwTerminate();

        INFO("Application terminated successfully.");
    }

    Engine::~Engine() {
        if (window) {
            glfwDestroyWindow(window);
            window = nullptr;
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
}
