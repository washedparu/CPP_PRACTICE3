#include <core.hpp>

int main() {
    Core::Engine engine;
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();


    engine.Init(1000,800,"Simple",monitor, nullptr);
    
    engine.Run();
    
    return EXIT_SUCCESS;
}