#ifndef CORE_HPP
#define CORE_HPP



#include "renderer.h"
namespace Core 
{
 class Engine { // Called engine for NOW.
public:
    static GLFWwindow* window; 
    


    // Initialize the application
    bool Init(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* shared);
    // Run the main loop
    void Run();
    // Draw Geometry
    void DrawGeometry();
    // Destructor to clean up resources
    ~Engine();
    // Create Shader 
    uint32_t CreateShader(const std::string& vertShader, const std::string& fragShader);
    // Compile Shader
    uint32_t compileShader(const std::string& source, uint32_t type);
    // Read shader from file
    static std::string ReadShaderFile(const std::string& filePath);

};

    class Math {
    public:
        std::vector<double> normalize(std::vector<float> p_values);
    };

}

#endif // CORE_HPP
