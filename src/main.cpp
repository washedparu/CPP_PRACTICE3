#include <core.hpp>

int main() {
    Core::Engine engine;
    
    engine.Init(100, 800, "Simple",nullptr, nullptr);
    
    engine.Run();
   
    
    return EXIT_SUCCESS;
}