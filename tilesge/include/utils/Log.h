//
// Created by DeKinci on 5/8/2020.
//

#ifndef TILESGE_LOG_H
#define TILESGE_LOG_H

#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>

class Log {
public:
    static void init(const std::string &file, bool debug);

    template<typename... Args>
    inline static void trace(const std::string &fmt, const Args &... args) {
        spdlog::trace(spdlog::string_view_t(fmt), args...);
    }

    template<typename... Args>
    inline static void debug(const std::string &fmt, const Args &... args) {
        spdlog::debug(spdlog::string_view_t(fmt), args...);
    }

    template<typename... Args>
    inline static void info(const std::string &fmt, const Args &... args) {
        spdlog::info(spdlog::string_view_t(fmt), args...);
    }

    template<typename... Args>
    inline static void warn(const std::string &fmt, const Args &... args) {
        spdlog::warn(spdlog::string_view_t(fmt), args...);
    }

    template<typename... Args>
    inline static void error(const std::string &fmt, const Args &... args) {
        spdlog::error(spdlog::string_view_t(fmt), args...);
    }

    template<typename... Args>
    inline static void critical(const std::string &fmt, const Args &... args) {
        spdlog::critical(spdlog::string_view_t(fmt), args...);
    }

    template<typename T>
    inline static void trace(const T &msg) {
        spdlog::trace(msg);
    }

    template<typename T>
    inline static void debug(const T &msg) {
        spdlog::debug(msg);
    }

    template<typename T>
    inline static void info(const T &msg) {
        spdlog::info(msg);
    }

    template<typename T>
    inline static void warn(const T &msg) {
        spdlog::warn(msg);
    }

    template<typename T>
    inline static void error(const T &msg) {
        spdlog::error(msg);
    }

    template<typename T>
    inline static void critical(const T &msg) {
        spdlog::critical(msg);
    }
};


#endif //TILESGE_LOG_H
