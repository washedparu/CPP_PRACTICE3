#pragma once

// Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

//macros

#define INFO(fmt, ...) spdlog::info(fmt, ##__VA_ARGS__)
#define ERROR(fmt, ...) spdlog::error(fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) spdlog::debug(fmt, ##__VA_ARGS__)
#define WARN(fmt, ...) spdlog::warn(fmt, ##__VA_ARGS__)
#define CRITIC(fmt, ...) spdlog::critical(fmt, ##__VA_ARGS__)

#define FAILED -1

// ASSERT macro
