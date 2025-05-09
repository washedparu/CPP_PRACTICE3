#include <core.hpp>

int main() {
    Core::Engine engine;


    engine.Init(1000,800,"Simple",nullptr, nullptr);
    
    engine.Run();
    
    return EXIT_SUCCESS;
}