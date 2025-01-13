#include "core.hpp"

namespace Core {
    GLFWwindow* Engine::m_Window = nullptr; // Fixed missing Engine:: scope for m_Window
    std::vector<float> vertices;

    
    // Initialize the application
    bool Engine::Init(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* shared) {
        // Initialize GLFW
        if (!glfwInit()) {
            ERROR("Failed initializing GLFW.");
            return false;
        }
        INFO("GLFW initialized successfully.");

        // Create a window
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_ACCUM_RED_BITS, GLFW_DONT_CARE); // Fixed invalid hint value

        m_Window = glfwCreateWindow(width, height, title, monitor, shared);

        if (!m_Window) {
            glfwTerminate();
            ERROR("Couldn't create window!");
            return false;
        }
        INFO("Created window successfully.");

        glfwMakeContextCurrent(m_Window);

        // Initialize GLEW
        glewExperimental = GL_TRUE; // Required for core profile compatibility
        if (glewInit() != GLEW_OK) {
            ERROR("Couldn't initialize GLEW!");
            glfwDestroyWindow(m_Window); // Clean up resources
            glfwTerminate();
            return false;
        }
        INFO("GLEW initialized successfully!");

        return true;
    }

    // Draw geometries
    void Engine::DrawGeometrie() { // Fixed method signature and moved outside of Run
        // Draw a quad
        glDrawArrays(GL_QUADS,0,4);
    }

    // Run the main loop
    void Engine::Run() {
        if (!m_Window) {
            ERROR("Window is not initialized. Call Core::Init() first.");
            return;
        }

        // Print out GL Version
        INFO("GL version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

        vertices.reserve(3 * 8);


        vertices.insert(vertices.end(), {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f
        });

        uint32_t buffer;        
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, vertices.data(), GL_STATIC_DRAW);
        


        while (!glfwWindowShouldClose(m_Window)) {
            // Clear the screen
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            
            DrawGeometrie();
            // Swap buffers and poll events
            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }

        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    // Destructor to clean up resources
    Engine::~Engine() {
        if (m_Window) {
            glfwDestroyWindow(m_Window);
            glfwTerminate();
        }
    }
}
