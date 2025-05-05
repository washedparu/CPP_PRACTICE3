cmake_minimum_required(VERSION 3.10)

# Project name and version
project(OpenGLApp VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
file(GLOB_RECURSE src "src/*.cpp")

# Include Directory
include_directories(include)

# Add the executable
add_executable(OpenGL ${src})

# Link libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(spdlog REQUIRED)


target_link_libraries(OpenGL
    OpenGL::GL
    glfw
    GLEW::GLEW
    spdlog::spdlog
)