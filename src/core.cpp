#include <core.hpp>
#include <renderer.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <BufferLayout.h>

namespace Core {
    GLFWwindow* Engine::window = nullptr;;

 

    // Returns a string that has the file content
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

    struct Shaders {
        std::string vertShader = Engine::ReadShaderFile("../res/shaders/shader.vert");
        std::string fragShader = Engine::ReadShaderFile("../res/shaders/shader.frag");
    };

    bool Engine::Init(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* shared) {

        if (!glfwInit()) {
            ERROR("Failed initializing GLFW.");
            return false;
        }
        INFO("GLFW initialized successfully.");

        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

        window = glfwCreateWindow(width, height, title, monitor, shared);
        if (!window) {
            glfwTerminate();
            ERROR("Couldn't create window!");
            return false;
        }
        INFO("Created window successfully.");

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            ERROR("Failed to initialize GLAD");
            return false;
        }
        INFO("GLAD initialized.");

        return true;
    }

    

    void Engine::Run() {
        Shaders shaders;
        if (!window) {
            ERROR("Window is not initialized. Call Core::Init() first.");
            Init(400,400,"Default",nullptr,nullptr);
        }

        float vertices[8] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f
        };

        unsigned int indices[5] = {0,1,2,2,3};

    
        
        VertexArray va;
        VertexBuffer vb(vertices, 8 * sizeof(float));
        BufferLayout layout;
        va.addBuffer(vb, layout);


        IndexBuffer ib(indices, 6);

        if (shaders.vertShader.empty() || shaders.fragShader.empty()) {
            ERROR("Failed to load shaders. Exiting application.");
            return;
        }

        unsigned int shader = CreateShader(shaders.vertShader, shaders.fragShader);
        if (!shader) {
            ERROR("Shader program creation failed.");
            return;
        }

        GLCall(glUseProgram(shader));
        int colorLoc = glGetUniformLocation(shader, "u_color");

        while (!glfwWindowShouldClose(window)) {
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            float timeValue = static_cast<float>(glfwGetTime());
            if(timeValue == 0.0) ERROR("TimeValue is set to {}",timeValue);

            GLCall(glUniform1f(colorLoc, timeValue));
            vb.Bind();
            ib.Bind();


            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        vb.unBind();
        ib.unBind();
        GLCall(glDeleteProgram(shader));  
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    Engine::~Engine() {
        if (window) {
            glfwDestroyWindow(window);
            window = nullptr;
        }
        INFO("Application terminated successfully.");
        glfwTerminate();
    }

    unsigned int Engine::compileShader(const std::string& source, unsigned int type) {
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

    unsigned int Engine::CreateShader(const std::string& vertShader, const std::string& fragShader) {
        unsigned int program = glCreateProgram();
        unsigned int vs = compileShader(vertShader, GL_VERTEX_SHADER);
        unsigned int fs = compileShader(fragShader, GL_FRAGMENT_SHADER);
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
}
