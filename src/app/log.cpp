/*
 * Created by Lucas Gracioso <contact@lbgracioso.net>
 * SPDX-License-Identifier: GPL-3.0-only
*/

#include "log.h"

std::shared_ptr<spdlog::logger> Log::logger = nullptr;

void Log::init() {
    if (!logger) {
        try {
            logger = spdlog::basic_logger_mt("responder", "responder.log");
            spdlog::set_default_logger(logger);
            spdlog::set_level(spdlog::level::info);
            spdlog::flush_on(spdlog::level::info);
        } catch (const spdlog::spdlog_ex& ex) {
            fmt::println("Log initialization failed: {}", ex.what());
        }
    }
}

void Log::shutdown() {
    if (logger) {
        spdlog::shutdown();
    }
}
