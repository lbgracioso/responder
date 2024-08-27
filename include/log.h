/*
 * Created by Lucas Gracioso <contact@lbgracioso.net>
 * SPDX-License-Identifier: Apache-2.0
*/

#ifndef LOG_H
#define LOG_H
#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

class Log {
private:
    static std::shared_ptr<spdlog::logger> logger;

    template <typename... Args>
    static void log(spdlog::level::level_enum level, fmt::format_string<Args...> fmt, Args&&... args) {
        if (logger) {
            try {
                std::string formatted_message = fmt::format(fmt, std::forward<Args>(args)...);
                logger->log(level, formatted_message);
            } catch (const fmt::format_error& e) {
                fmt::println("Logging error: {}", e.what());
            }
        } else {
            fmt::println("Logger not initialized!");
        }
    }

public:
    static void init();

    template <typename... Args>
    static void Info(fmt::format_string<Args...> fmt, Args&&... args) {
        log(spdlog::level::info, fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void Error(fmt::format_string<Args...> fmt, Args&&... args) {
        log(spdlog::level::err, fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void Warn(fmt::format_string<Args...> fmt, Args&&... args) {
        log(spdlog::level::warn, fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void Debug(fmt::format_string<Args...> fmt, Args&&... args) {
        log(spdlog::level::debug, fmt, std::forward<Args>(args)...);
    }

    static void shutdown();
};



#endif //LOG_H
