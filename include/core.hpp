#ifndef CORE_HPP
#define CORE_HPP


// Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <cstdlib> 
#include <fstream>
#include <sstream>
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
    // Create Shader 
    uint32_t CreateShader(const std::string& vertShader, const std::string& fragShader);
    // Compile Shader
    uint32_t compileShader(const std::string& source, uint32_t type);
    static GLFWwindow* m_Window; 
};

    class Math {
    public:
        std::vector<double> normalize(std::vector<float> p_values);
    };

}

#endif // CORE_HPP
