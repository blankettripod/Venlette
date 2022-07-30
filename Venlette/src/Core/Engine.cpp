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
        return VEN_SUCCESS;

        failed:
        spdlog::critical("[SYSTEM] Failed to initialise: Critical module failed to initialise");
        return VEN_FAILURE;
    }

    VEN_RESULT Engine::Shutdown() noexcept {
        VEN_CORE_INFO("[SYSTEM] Shutting Down");

        spdlog::info("[SYSTEM] Shut Down");
        return 0;
    }
} // Core