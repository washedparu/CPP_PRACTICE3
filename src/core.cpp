#include "core.hpp"

namespace Core {

// Global variables for GLFW window
GLFWwindow* window = nullptr;

// Initialize the application
bool Init(int width ,int height, const char* title, GLFWmonitor *monitor,GLFWwindow *shared) {
    // Initialize GLFW
    if (!glfwInit()) {
        spdlog::error("Failed initializing GLFW.");
        return false;
    }
    spdlog::info("GLFW initialized successfully.");

    // Create a window
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 
    glfwWindowHint(GLFW_ACCUM_RED_BITS, GL_TRUE);
    window = glfwCreateWindow(width,height,title, monitor, shared);
    if (!window) {
        glfwTerminate();
        spdlog::error("Couldn't create window!");
        return false;
    }
    spdlog::info("Created window successfully.");

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        spdlog::error("Couldn't initialize GLEW!");
        return false;
    }
    spdlog::info("GLEW initialized successfully!");

    return true;
}

// Run the main loop
void Run() {
    if (!window) {
        spdlog::error("Window is not initialized. Call Core::Init() first.");
        return;
    }

    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glColor3f(0.0f, 1.0f, 0.0f);

        // Call the drawGeometrie function
        drawGeometrie();

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

// Draw geometry
void drawGeometrie() {
    // Draw a quad
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();

    // Draw a triangle
    glColor3f(0.0f, -0.5f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();
}

} // namespace Core
