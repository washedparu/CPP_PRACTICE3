cmake_minimum_required(VERSION 3.10)

project(CPP_PRACTICE)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)


file(GLOB_RECURSE src "src/*.cpp")

include_directories(include)

add_executable(OpenGL ${src})

target_link_libraries(OpenGL OpenGL::GL glfw)