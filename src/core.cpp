#include <core.hpp>
#include <renderer.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <BufferLayout.h>
#include <Shader.h>

namespace Core {
    GLFWwindow* Engine::window = nullptr;;

 
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

        unsigned int indices[6] = {0,1,2,2,3,0};

    


        VertexArray va;
        VertexBuffer vb(vertices, 8 * sizeof(float));
        BufferLayout layout;
        layout.push<float>(2);

        va.addBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        Shader shader("../res/shaders/shader.vert", "../res/shaders/shader.frag");
        shader.Bind();
        
        float time = glfwGetTime();
        shader.SetUniform1f("u_color",time);

        va.unBind();
        vb.unBind();
        ib.unBind();
        shader.UnBind();


        while (!glfwWindowShouldClose(window)) {
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            shader.Bind();
            shader.SetUniform1f("u_color", time);
            va.Bind();
            ib.Bind();

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
            glfwSwapBuffers(window);
            glfwPollEvents();
        } 
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

   
}
