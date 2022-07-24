//
// Created by reece on 22/07/22.
//

#include "Core/System.h"
#include "Util/Logging/Logger.h"
#include "Core/Events/EventManager.h"
#include "GLFW/glfw3.h"


namespace Venlette {
void System::Init() noexcept {
    Util::Logger::Init();
    Events::EventManager::Init();
    glfwInit();
}

void System::Shutdown() noexcept {
    Events::EventManager::Shutdown();
    glfwTerminate();
}
} // Venlette