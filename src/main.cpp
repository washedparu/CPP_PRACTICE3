#include <core.hpp>

int main() {
    if (!Core::Init()) {
        return  EXIT_SUCCESS;
    }

    Core::Run();

    return EXIT_SUCCESS;
}
