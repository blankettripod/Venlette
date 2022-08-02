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

    static Logging* Get() noexcept;

    [[nodiscard]] std::optional<std::shared_ptr<spdlog::logger>> GetCoreLogger() const noexcept;
    [[nodiscard]] std::optional<std::shared_ptr<spdlog::logger>> GetClientLogger() const noexcept;

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
    auto logger_instance = ::Venlette::Util::Logging::Get(); \
    if (logger_instance) \
    { \
        auto logger_core_instance = logger_instance->GetCoreLogger(); \
        if (logger_core_instance.has_value()) logger_core_instance->get()->trace(__VA_ARGS__); \
    } \
} END_MACRO

#define VEN_CORE_INFO(...) { \
auto logger_instance = ::Venlette::Util::Logging::Get(); \
    if (logger_instance) \
    { \
        auto logger_core_instance = logger_instance->GetCoreLogger(); \
        if (logger_core_instance.has_value()) logger_core_instance->get()->info(__VA_ARGS__); \
    } \
} END_MACRO

#define VEN_CORE_WARN(...) { \
auto logger_instance = ::Venlette::Util::Logging::Get(); \
    if (logger_instance) \
    { \
        auto logger_core_instance = logger_instance->GetCoreLogger(); \
        if (logger_core_instance.has_value()) logger_core_instance->get()->warn(__VA_ARGS__); \
    } \
} END_MACRO

#define VEN_CORE_ERROR(...) { \
auto logger_instance = ::Venlette::Util::Logging::Get(); \
    if (logger_instance) \
    { \
        auto logger_core_instance = logger_instance->GetCoreLogger(); \
        if (logger_core_instance.has_value()) logger_core_instance->get()->error(__VA_ARGS__); \
    } \
} END_MACRO

#define VEN_CORE_FATAL(...) { \
auto logger_instance = ::Venlette::Util::Logging::Get(); \
    if (logger_instance) \
    { \
        auto logger_core_instance = logger_instance->GetCoreLogger(); \
        if (logger_core_instance.has_value()) logger_core_instance->get()->critical(__VA_ARGS__); \
    } \
} END_MACRO

#define VEN_CLIENT_TRACE(...) { \
auto logger_instance = ::Venlette::Util::Logging::Get(); \
    if (logger_instance) \
    { \
        auto logger_core_instance = logger_instance->GetCoreLogger(); \
        if (logger_core_instance.has_value()) logger_core_instance->get()->trace(__VA_ARGS__); \
    } \
} END_MACRO

#define VEN_CLIENT_INFO(...) { \
auto logger_instance = ::Venlette::Util::Logging::Get(); \
    if (logger_instance) \
    { \
        auto logger_core_instance = logger_instance->GetCoreLogger(); \
        if (logger_core_instance.has_value()) logger_core_instance->get()->info(__VA_ARGS__); \
    } \
} END_MACRO

#define VEN_CLIENT_WARN(...) { \
auto logger_instance = ::Venlette::Util::Logging::Get(); \
    if (logger_instance) \
    { \
        auto logger_core_instance = logger_instance->GetCoreLogger(); \
        if (logger_core_instance.has_value()) logger_core_instance->get()->warn(__VA_ARGS__); \
    } \
} END_MACRO

#define VEN_CLIENT_ERROR(...) { \
auto logger_instance = ::Venlette::Util::Logging::Get(); \
    if (logger_instance) \
    { \
        auto logger_core_instance = logger_instance->GetCoreLogger(); \
        if (logger_core_instance.has_value()) logger_core_instance->get()->error(__VA_ARGS__); \
    } \
} END_MACRO

#define VEN_CLIENT_FATAL(...) { \
auto logger_instance = ::Venlette::Util::Logging::Get(); \
    if (logger_instance) \
    { \
        auto logger_core_instance = logger_instance->GetCoreLogger(); \
        if (logger_core_instance.has_value()) logger_core_instance->get()->critical(__VA_ARGS__); \
    } \
} END_MACRO

} // Util