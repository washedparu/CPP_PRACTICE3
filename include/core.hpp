#ifndef CORE_HPP
#define CORE_HPP


// Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <cstdlib> 

namespace Core {
    // Initialize the application
    bool Init(int width ,int height, const char* title, GLFWmonitor *monitor,GLFWwindow *shared);

    // Run the main loop
    void Run();

    // Function for drawing geometry
    void drawGeometrie();
}

#endif // CORE_HPP
