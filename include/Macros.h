#pragma once

// Includes
#include <iostream>
#include <spdlog/spdlog.h>
#include <csignal>

// ASSERT macro 

#define ASSERT(x) if (!(x)) raise(SIGTRAP)
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__ ))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);


//macros

#define INFO(fmt, ...) spdlog::info(fmt, ##__VA_ARGS__)
#define ERROR(fmt, ...) spdlog::error(fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) spdlog::debug(fmt, ##__VA_ARGS__)
#define WARN(fmt, ...) spdlog::warn(fmt, ##__VA_ARGS__)
#define CRITIC(fmt, ...) spdlog::critical(fmt, ##__VA_ARGS__)

#define FAILED -1

