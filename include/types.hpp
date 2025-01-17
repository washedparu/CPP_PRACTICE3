#pragma once
#include <spdlog/spdlog.h>
//macros

#define INFO(fmt, ...) spdlog::info(fmt, ##__VA_ARGS__) 
#define ERROR(fmt, ...)     spdlog::error(fmt, ##__VA_ARGS__) 
#define DEBUG(fmt, ...)     spdlog::debug(fmt, ##__VA_ARGS__) 
#define WARN(fmt, ...)     spdlog::warn(fmt, ##__VA_ARGS__) 
#define CRITIC(fmt, ...)     spdlog::critical(fmt, ##__VA_ARGS__) 

#define FAILED -1
