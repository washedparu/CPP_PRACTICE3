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
    bool Init();

    // Run the main loop
    void Run();

    // Function for drawing geometry
    void drawGeometrie();
}

#endif // CORE_HPP
