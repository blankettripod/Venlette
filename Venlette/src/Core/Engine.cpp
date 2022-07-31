//
// Created by reece on 28/07/22.
//

#include "Core/Engine.h"
#include "Core/internal.h"


namespace Venlette::Core {
    VEN_RESULT Engine::Init() noexcept {
        spdlog::info("[SYSTEM] Initialising");

        if (FAILED(Util::Logging::Init())) goto failed;


        VEN_CORE_INFO("[SYSTEM] Initialised");
        s_isInitialised = true;
        return VEN_SUCCESS;

        failed:
        spdlog::critical("[SYSTEM] Failed to initialise: Critical module failed to initialise");
        s_isInitialised = false;
        return VEN_FAILURE;
    }

    VEN_RESULT Engine::Shutdown() noexcept {
        VEN_CORE_INFO("[SYSTEM] Shutting Down");

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