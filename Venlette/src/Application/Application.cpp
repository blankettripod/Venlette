//
// Created by reece on 30/07/22.
//

#include "Application/Application.h"
#include "Core/internal.h"

namespace Venlette::Application {

    bool Application::isRunning() const noexcept {
        return m_isRunning;
    }

    VEN_RESULT Application::run() noexcept {
        VEN_CORE_INFO("[APPLICATION] Running application");
        m_isRunning = true;
        return VEN_SUCCESS;
    }

    VEN_RESULT Application::kill() noexcept {
        VEN_CORE_INFO("[APPLICATION] Killing application");
        m_isRunning = false;
        return VEN_SUCCESS;
    }

} // Application