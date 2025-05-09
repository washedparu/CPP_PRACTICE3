#pragma once

// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <csignal>


//macros

#define INFO(fmt, ...) spdlog::info(fmt, ##__VA_ARGS__)
#define ERROR(fmt, ...) spdlog::error(fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) spdlog::debug(fmt, ##__VA_ARGS__)
#define WARN(fmt, ...) spdlog::warn(fmt, ##__VA_ARGS__)
#define CRITIC(fmt, ...) spdlog::critical(fmt, ##__VA_ARGS__)

#define FAILED -1

// ASSERT macro (f*cking finally.)

#define ASSERT(x) if (!(x)) raise(SIGTRAP)
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

inline void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

inline bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): "
                  << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}
