#include <core.hpp>

int main() {
    if (!Core::Init(800,600,"OpenGL",NULL,NULL)) {
        return  EXIT_SUCCESS;
    }

    Core::Run();

    return EXIT_SUCCESS;
}
