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

#define VEN_CORE_TRACE(...) ::Venlette::Util::Logger::GetCoreLogger()->trace(__VA_ARGS__, " {}:{}", __FILE__, __LINE__)
#define VEN_CORE_INFO(...) ::Venlette::Util::Logger::GetCoreLogger()->info(__VA_ARGS__, " {}:{}", __FILE__, __LINE__)
#define VEN_CORE_WARN(...) ::Venlette::Util::Logger::GetCoreLogger()->warn(__VA_ARGS__, " {}:{}", __FILE__, __LINE__)
#define VEN_CORE_ERROR(...) ::Venlette::Util::Logger::GetCoreLogger()->error(__VA_ARGS__, " {}:{}", __FILE__, __LINE__)
#define VEN_CORE_CRITICAL(...) ::Venlette::Util::Logger::GetCoreLogger()->critical(__VA_ARGS__, " {}:{}", __FILE__, __LINE__)

#define VEN_CLIENT_TRACE(...) ::Venlette::Util::Logger::GetClientLogger()->trace(__VA_ARGS__, " {}:{}", __FILE__, __LINE__)
#define VEN_CLIENT_INFO(...) ::Venlette::Util::Logger::GetClientLogger()->info(__VA_ARGS__, " {}:{}", __FILE__, __LINE__)
#define VEN_CLIENT_WARN(...) ::Venlette::Util::Logger::GetClientLogger()->warn(__VA_ARGS__, " {}:{}", __FILE__, __LINE__)
#define VEN_CLIENT_ERROR(...) ::Venlette::Util::Logger::GetClientLogger()->error(__VA_ARGS__, " {}:{}", __FILE__, __LINE__)
#define VEN_CLIENT_CRITICAL(...) ::Venlette::Util::Logger::GetClientLogger()->critical(__VA_ARGS__, " {}:{}", __FILE__, __LINE__)
