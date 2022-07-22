//
// Created by reece on 22/07/22.
//

#include <new>

#include "Core/common.h"
#include "Util/Logging/Logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Venlette::Util {

void Logger::Init() noexcept {
    // create the spdlog sinks

    // file sink
    auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Venlette.log", true);
    fileSink->set_pattern("%^[%T] %n: %v%$");

    // console sink
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    consoleSink->set_pattern("%^[%M:%S] %n: %v%$");

    // create the core logger
    s_coreLogger = std::make_shared<spdlog::logger>("Venlette", spdlog::sinks_init_list{fileSink, consoleSink});
    s_coreLogger->set_level(spdlog::level::trace);

    // create the client logger
    s_clientLogger = std::make_shared<spdlog::logger>("Client", spdlog::sinks_init_list{fileSink, consoleSink});
    s_clientLogger->set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger> Logger::GetCoreLogger() noexcept {
    return s_coreLogger;
}

std::shared_ptr<spdlog::logger> Logger::GetClientLogger() noexcept {
    return s_clientLogger;
}

std::shared_ptr<spdlog::logger> Logger::s_coreLogger;
std::shared_ptr<spdlog::logger> Logger::s_clientLogger;
} // Util