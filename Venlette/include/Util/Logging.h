//
// Created by reece on 28/07/22.
//

#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/logger.h>

#include "Core/common.h"

namespace Venlette::Core{class Engine;}

namespace Venlette::Util {
class Logging {
public:

    [[nodiscard]] static std::optional<std::shared_ptr<spdlog::logger>> GetCoreLogger() noexcept;
    [[nodiscard]] static std::optional<std::shared_ptr<spdlog::logger>> GetClientLogger() noexcept;

protected:
    friend class Venlette::Core::Engine;

    static VEN_RESULT Init() noexcept;
    static VEN_RESULT Shutdown() noexcept;
private:

    Logging();
    ~Logging();

    static Logging* s_instance;

    std::shared_ptr<spdlog::logger> m_coreLogger;
    std::shared_ptr<spdlog::logger> m_clientLogger;
};


//  static_assert(true, "") is for requiring a semicolon after the call
#define VEN_CORE_TRACE(...) { \
        auto logger_core_instance = ::Venlette::Util::Logging::GetCoreLogger(); \
        if (logger_core_instance.has_value()) logger_core_instance->get()->trace(__VA_ARGS__); \
} END_MACRO

#define VEN_CORE_INFO(...) { \
        auto logger_core_instance = ::Venlette::Util::Logging::GetCoreLogger(); \
        if (logger_core_instance.has_value()) logger_core_instance->get()->info(__VA_ARGS__); \
} END_MACRO

#define VEN_CORE_WARN(...) { \
        auto logger_core_instance = ::Venlette::Util::Logging::GetCoreLogger(); \
        if (logger_core_instance.has_value()) logger_core_instance->get()->warn(__VA_ARGS__); \
} END_MACRO

#define VEN_CORE_ERROR(...) { \
        auto logger_core_instance = ::Venlette::Util::Logging::GetCoreLogger(); \
        if (logger_core_instance.has_value()) logger_core_instance->get()->error(__VA_ARGS__); \
} END_MACRO

#define VEN_CORE_FATAL(...) { \
        auto logger_core_instance = ::Venlette::Util::Logging::GetCoreLogger(); \
        if (logger_core_instance.has_value()) logger_core_instance->get()->critical(__VA_ARGS__); \
} END_MACRO

#define VEN_CLIENT_TRACE(...) { \
        auto logger_client_instance = ::Venlette::Util::Logging::GetClientLogger(); \
        if (logger_client_instance.has_value()) logger_client_instance->get()->trace(__VA_ARGS__); \
} END_MACRO

#define VEN_CLIENT_INFO(...) { \
        auto logger_client_instance = ::Venlette::Util::Logging::GetClientLogger(); \
        if (logger_client_instance.has_value()) logger_client_instance->get()->info(__VA_ARGS__); \
} END_MACRO

#define VEN_CLIENT_WARN(...) { \
        auto logger_client_instance = ::Venlette::Util::Logging::GetClientLogger(); \
        if (logger_client_instance.has_value()) logger_client_instance->get()->warn(__VA_ARGS__); \
} END_MACRO

#define VEN_CLIENT_ERROR(...) { \
        auto logger_client_instance = ::Venlette::Util::Logging::GetClientLogger(); \
        if (logger_client_instance.has_value()) logger_client_instance->get()->error(__VA_ARGS__); \
} END_MACRO

#define VEN_CLIENT_FATAL(...) { \
        auto logger_client_instance = ::Venlette::Util::Logging::GetClientLogger(); \
        if (logger_client_instance.has_value()) logger_client_instance->get()->critical(__VA_ARGS__); \
} END_MACRO

/*
#define VEN_CORE_INFO(...)
#define VEN_CORE_WARN(...)
#define VEN_CORE_ERROR(...)
#define VEN_CORE_FATAL(...)
#define VEN_CORE_TRACE(...)
#define VEN_CLIENT_INFO(...)
#define VEN_CLIENT_WARN(...)
#define VEN_CLIENT_ERROR(...)
#define VEN_CLIENT_FATAL(...)
#define VEN_CLIENT_TRACE(...)*/

} // Util