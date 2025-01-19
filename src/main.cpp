#include <core.hpp>



int main() {
    using namespace Core;


    Engine engine;
    if(!engine.Init(800,600,"OpenGL",NULL,NULL))
        return FAILED;

    engine.Run();
    
    return EXIT_SUCCESS;
}