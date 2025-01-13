#include <core.hpp>

int main() {
    using namespace Core;


   auto engine = std::make_unique<Engine>();


    if(!engine->Init(800,600,"OpenGL",NULL,NULL)) 
        return -1;
        
    engine->Run();
    return EXIT_SUCCESS;
}
