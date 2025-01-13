#ifndef CORE_HPP
#define CORE_HPP


// Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <cstdlib> 
#include "types.hpp"

namespace Core {
 class Engine { // Called engine for NOW.
public:
    // Initialize the application
    bool Init(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* shared);

    // Run the main loop
    void Run();

    // Draw Geometry
    void DrawGeometrie();

    // Destructor to clean up resources
    ~Engine();

    
    static GLFWwindow* m_Window; 
};

}

#endif // CORE_HPP
