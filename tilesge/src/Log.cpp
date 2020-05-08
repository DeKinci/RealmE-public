//
// Created by DeKinci on 5/8/2020.
//

#include "Log.h"

void Log::init(const std::string &file, bool debug) {
    spdlog::init_thread_pool(8192, 1);
    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    stdout_sink->set_level(spdlog::level::info);
    auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file, 1024 * 1024 * 10, 3, true);
    rotating_sink->set_level(spdlog::level::debug);
    std::vector<spdlog::sink_ptr> sinks{stdout_sink, rotating_sink};
    auto logger = std::make_shared<spdlog::async_logger>(
            "loggername",
            sinks.begin(),
            sinks.end(),
            spdlog::thread_pool(),
            spdlog::async_overflow_policy::overrun_oldest
    );
    spdlog::register_logger(logger);
    spdlog::set_default_logger(logger);
    spdlog::flush_on(debug ? spdlog::level::debug : spdlog::level::warn);

    spdlog::set_pattern("[%H:%M:%S %z %n %^%L%$ t=%t] %v");
    spdlog::set_level(debug ? spdlog::level::debug : spdlog::level::info);
    spdlog::info("Logger initialized");
}
