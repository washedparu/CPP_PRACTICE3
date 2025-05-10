cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Simple VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
file(GLOB_RECURSE src "src/*.cpp")

# Include Directory
include_directories(include)

# Add the executable
add_executable(Simple 
    src/main.cpp 
    src/core.cpp 
    src/VertexBuffer.cpp 
    src/IndexBuffer.cpp 
    src/VertexArray.cpp
    src/glad.cpp 
    src/renderer.cpp 
    src/Shader.cpp
)

# Adding glad because glew is making me go insane
add_library(glad STATIC src/glad.cpp)
target_include_directories(glad PUBLIC include)

# Link libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)


target_link_libraries(${PROJECT_NAME}
  PRIVATE
    glad
    glfw
    OpenGL::GL
    spdlog::spdlog
)