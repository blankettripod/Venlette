//
// Created by reece on 28/07/22.
//
#include "Util/Logging.h"
#include "Core/internal.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Venlette::Util {

    VEN_RESULT Logging::Init() noexcept {
        spdlog::info("[LOGGING] Initialising");

        if (s_instance) {
            VEN_CORE_ERROR("[LOGGING] Failed to initialise: Already initialised");
            goto failed;
        }

        try {
            s_instance = new Logging;
        } catch (std::runtime_error& e) {
            spdlog::error("[LOGGING] Failed to create logger");
            goto failed;
        } catch (std::bad_alloc& e) {
            spdlog::error("[LOGGING] Failed to create logger: {}", e.what());
            goto failed;
        }

        spdlog::info("[LOGGING] Initialised");
        return VEN_SUCCESS;
        failed:
        return VEN_FAILURE;
    }

    VEN_RESULT Logging::Shutdown() noexcept {
        spdlog::info("[LOGGING] Shutting down");
        if (!s_instance) {
            spdlog::error("[LOGGING] Failed to shutdown: Logger is not available");
            return VEN_FAILURE;
        }

        delete s_instance;
        s_instance = nullptr;

        spdlog::info("[LOGGING] Shut down");
        return VEN_SUCCESS;
    }

    std::optional<std::shared_ptr<spdlog::logger>> Logging::GetCoreLogger() const noexcept {
        if (m_coreLogger == nullptr) {
            spdlog::error("[LOGGING] Cannot Get Core Logging: Not available");
            return std::nullopt;
        }

        return m_coreLogger;
    }

    std::optional<std::shared_ptr<spdlog::logger>> Logging::GetClientLogger() const noexcept {
        if (m_coreLogger == nullptr) {
            spdlog::error("[LOGGING] Cannot Get Client Logging: Not initialized");
            return std::nullopt;
        }
        return m_clientLogger;
    }

    Logging* Logging::s_instance = nullptr;

    Logging::Logging() {
        // create the spdlog sinks

        // file sink
        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Venlette.log", true);
        fileSink->set_pattern("%^[%T] %n: %v%$");

        // console sink
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_pattern("%^[%M:%S] %n: %v%$");

        // create the core Logging
        m_coreLogger = std::make_shared<spdlog::logger>("Venlette", spdlog::sinks_init_list{fileSink, consoleSink});
        m_coreLogger->set_level(spdlog::level::trace);

        // create the client Logging
        m_clientLogger = std::make_shared<spdlog::logger>("Client", spdlog::sinks_init_list{fileSink, consoleSink});
        m_clientLogger->set_level(spdlog::level::trace);

    }

    Logging *Logging::Get() noexcept {
        if (!s_instance) {
            spdlog::error("[LOGGING] Failed to get logging instance: Instance not available");
            return nullptr;
        }
        return s_instance;
    }

    Logging::~Logging() = default;
} // Util