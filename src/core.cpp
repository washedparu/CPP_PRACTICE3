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

        // Cube vertex data (x, y, z)
        static std::vector<float> vertices = {
            // Front face
            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            // Back face
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f
        };

        static std::vector<uint32_t> indices = {
            // Front face
            0, 1, 2, 2, 3, 0,
            // Back face
            4, 5, 6, 6, 7, 4,
            // Left face
            0, 3, 7, 7, 4, 0,
            // Right face
            1, 2, 6, 6, 5, 1,
            // Top face
            3, 2, 6, 6, 7, 3,
            // Bottom face
            0, 1, 5, 5, 4, 0
        };

        uint32_t vao, vbo, ebo;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        std::string vertShader = ReadFile("../res/shaders/vert.glsl");
        std::string fragShader = ReadFile("../res/shaders/frag.glsl");

        if (vertShader.empty() || fragShader.empty()) {
            ERROR("Failed to load shaders. Exiting application.");
            return;
        }

        unsigned int shader = CreateShader(vertShader, fragShader);
        glUseProgram(shader);

        // Set up transformations
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(shader, "model");
        int viewLoc = glGetUniformLocation(shader, "view");
        int projLoc = glGetUniformLocation(shader, "projection");

        while (!glfwWindowShouldClose(m_Window)) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Rotate the cube over time
            float timeValue = static_cast<float>(glfwGetTime());
            model = glm::rotate(glm::mat4(1.0f), timeValue, glm::vec3(0.5f, 1.0f, 0.0f));

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
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
