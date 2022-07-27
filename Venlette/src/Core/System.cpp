//
// Created by reece on 22/07/22.
//


#include "Core/System.h"

#include "Core/common.h"
#include "Core/Events/EventManager.h"
#include "Window/WindowManager.h"


namespace Venlette {
void System::Init() noexcept {

    if (s_initialised) {
        VEN_CORE_ERROR("[SYSTEM] Already initialised. This can cause issues with shutdown as systems attempt to "
                       "shutdown multiple times");
        return;
    }

    Util::Logger::Init();
    VEN_CORE_INFO("[SYSTEM] Initialising");
    if (!Events::EventManager::Init()) goto failed;
    if (!Window::WindowManager::Init()) goto failed;

    VEN_CORE_INFO("[System] Initialised");
    s_initialised = true;
    return;

    failed:
    VEN_CORE_CRITICAL("[SYSTEM] Failed to initialise");
    exit(1);
}

void System::Shutdown() noexcept {
    VEN_CORE_INFO("[SYSTEM] Shutting Down");
    Window::WindowManager::Shutdown();
    Events::EventManager::Shutdown();
    VEN_CORE_INFO("[SYSTEM] Shut Down");
}


bool System::s_initialised = false;
} // Venlette