//
// Created by reece on 22/07/22.
//

#pragma once

#include <spdlog/logger.h>
#include <memory>

namespace Venlette::Util {

class Logger {
public:
    static void Init() noexcept;

    static std::shared_ptr<spdlog::logger> GetCoreLogger() noexcept;
    static std::shared_ptr<spdlog::logger> GetClientLogger() noexcept;

private:
    static std::shared_ptr<spdlog::logger> s_coreLogger;
    static std::shared_ptr<spdlog::logger> s_clientLogger;
};


} // Util


//  static_assert(true, "") is for requiring a semicolon after the call
#define VEN_CORE_TRACE(...) {auto logger = ::Venlette::Util::Logger::GetCoreLogger(); \
    if (logger) logger->trace(__VA_ARGS__, " {}:{}", __FILE__, __LINE__);} static_assert(true, "")
#define VEN_CORE_INFO(...) {auto logger = ::Venlette::Util::Logger::GetCoreLogger(); \
    if (logger) logger->info(__VA_ARGS__, " {}:{}", __FILE__, __LINE__);} static_assert(true, "")
#define VEN_CORE_WARN(...) {auto logger = ::Venlette::Util::Logger::GetCoreLogger(); \
    if (logger) logger->warn(__VA_ARGS__, " {}:{}", __FILE__, __LINE__);} static_assert(true, "")
#define VEN_CORE_ERROR(...) {auto logger = ::Venlette::Util::Logger::GetCoreLogger(); \
    if (logger) logger->error(__VA_ARGS__, " {}:{}", __FILE__, __LINE__);} static_assert(true, "")
#define VEN_CORE_CRITICAL(...) {auto logger = ::Venlette::Util::Logger::GetCoreLogger(); \
    if (logger) logger->critical(__VA_ARGS__, " {}:{}", __FILE__, __LINE__);} static_assert(true, "")

#define VEN_CLIENT_TRACE(...) {auto logger = ::Venlette::Util::Logger::GetClientLogger(); \
    if (logger) logger->trace(__VA_ARGS__, " {}:{}", __FILE__, __LINE__);} static_assert(true, "")
#define VEN_CLIENT_INFO(...) {auto logger = ::Venlette::Util::Logger::GetClientLogger(); \
    if (logger) logger->info(__VA_ARGS__, " {}:{}", __FILE__, __LINE__);} static_assert(true, "")
#define VEN_CLIENT_WARN(...) {auto logger = ::Venlette::Util::Logger::GetClientLogger(); \
    if (logger) logger->warn(__VA_ARGS__, " {}:{}", __FILE__, __LINE__);} static_assert(true, "")
#define VEN_CLIENT_ERROR(...) {auto logger = ::Venlette::Util::Logger::GetClientLogger(); \
    if (logger) logger->error(__VA_ARGS__, " {}:{}", __FILE__, __LINE__);} static_assert(true, "")
#define VEN_CLIENT_CRITICAL(...) {auto logger = ::Venlette::Util::Logger::GetClientLogger(); \
    if (logger) logger->critical(__VA_ARGS__, " {}:{}", __FILE__, __LINE__);} static_assert(true, "")
