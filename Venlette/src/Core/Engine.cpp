//
// Created by reece on 28/07/22.
//

#include "Core/Engine.h"
#include "Core/internal.h"

#include "Core/Events/EventManager.h"
#include "Core/Thread/ThreadManager.h"

namespace Venlette::Core {
    VEN_RESULT Engine::Init() noexcept {
        if (s_isInitialised) {
            spdlog::error("[SYSTEM] Already initialised");
            return VEN_FAILURE;
        }

        spdlog::info("[SYSTEM] Initialising");

        if (FAILED(Util::Logging::Init())) goto failed;
        if (FAILED(Threading::ThreadManager::Init())) goto failed;
        if (FAILED(Events::EventManager::Init())) goto failed;

        Threading::ThreadManager::Get()->RegisterThread(Threading::ThreadType::Engine);

        VEN_CORE_INFO("[SYSTEM] Initialised");
        s_isInitialised = true;
        return VEN_SUCCESS;

        failed:
        spdlog::critical("[SYSTEM] Failed to initialise: Critical module failed to initialise");
        s_isInitialised = false;
        return VEN_FAILURE;
    }

    VEN_RESULT Engine::Shutdown() noexcept {
        if (!s_isInitialised) {
            spdlog::error("[SYSTEM] Already shut down");
        }
        VEN_CORE_INFO("[SYSTEM] Shutting Down");

        if (FAILED(Events::EventManager::Shutdown())) goto failed;
        if (FAILED(Threading::ThreadManager::Shutdown())) goto failed;
        if (FAILED(Util::Logging::Shutdown())) goto failed;


        spdlog::info("[SYSTEM] Shut Down");
        s_isInitialised = false;
        return VEN_SUCCESS;

        failed:
        spdlog::critical("[SYSTEM] Failed to initialise: Critical module failed to initialise");
        s_isInitialised = false;
        return VEN_FAILURE;
    }

    bool Engine::s_isInitialised = false;
} // Core