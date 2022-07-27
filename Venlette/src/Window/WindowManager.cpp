//
// Created by reece on 24/07/22.
//

#include "Window/WindowManager.h"
#include "Core/common.h"
#include "Core/Events/EventManager.h"

namespace Venlette::Window {

    using namespace Events;

    int WindowManager::Init() noexcept {
        if (s_instance) {
            VEN_CORE_WARN("[WINDOW MANAGER] Already initialized!");

            delete s_instance;
            s_instance = nullptr;
        }
        try {
            s_instance = new WindowManager;
        } catch (const std::exception& e) {
            goto failed;
        }

        glfwSetErrorCallback(WindowManager::ErrorCallback);

        if (!glfwInit()) {
            goto failed;
        }

        VEN_CORE_INFO("[WINDOW MANAGER] Initialized!");
        return true;

        failed:
        delete s_instance;
        s_instance = nullptr;
        return false;
    }

    void WindowManager::Shutdown() noexcept {
        if (!s_instance) {
            VEN_CORE_ERROR("[WINDOW MANAGER] Cannot Shutdown: Not initialized!");
            return;
        }
        VEN_CORE_INFO("[WINDOW MANAGER] Shutting Down");

        delete s_instance;
        s_instance = nullptr;
        VEN_CORE_INFO("[WINDOW MANAGER] Shutdown");
    }

    WindowManager::WindowManager() noexcept {
    }

    WindowManager::~WindowManager() noexcept {
    }

    WindowManager* WindowManager::s_instance = nullptr;

    void WindowManager::ErrorCallback(int code, const char *description) noexcept {
        VEN_CORE_ERROR("[WINDOW MANAGER] GLFW ERROR: {}", description);
    }

    WindowManager *WindowManager::Get() noexcept {
        return s_instance;
    }

    void WindowManager::WindowPositionCallback(GLFWwindow *pWnd, int x, int y) noexcept {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(pWnd));
        Event event{};
        event.category = Event::Category::Window;
        event.pointer = window;
        event.type = Event::Type::WindowMove;
        event.data[0] = x;
        event.data[1] = y;

        EventManager::Get()->FireEvent(event);
    }

    void WindowManager::WindowResizeCallback(GLFWwindow *pWnd, int width, int height) noexcept {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(pWnd));
        Event event{};
        event.category = Event::Category::Window;
        event.pointer = window;
        event.type = Event::Type::WindowResize;
        event.data[0] = width;
        event.data[1] = height;

        EventManager::Get()->FireEvent(event);
    }

    void WindowManager::WindowCloseCallback(GLFWwindow *pWnd) noexcept {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(pWnd));
        Event event{};
        event.category = Event::Category::Window;
        event.pointer = window;
        event.type = Event::Type::WindowClose;

        EventManager::Get()->FireEvent(event);
    }

    void WindowManager::WindowFocusCallback(GLFWwindow *pWnd, int focused) noexcept {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(pWnd));
        Event event{};
        event.category = Event::Category::Window;
        event.pointer = window;
        event.type = focused? Event::Type::WindowGainFocus:Event::Type::WindowLoseFocus;

        EventManager::Get()->FireEvent(event);
    }

    void WindowManager::WindowMinimiseCallback(GLFWwindow *pWnd, int minimised) noexcept {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(pWnd));
        Event event{};
        event.category = Event::Category::Window;
        event.pointer = window;
        event.type = minimised? Event::Type::WindowMinimise:Event::Type::WindowRestore;

        glfwGetWindowSize(window->getWindow(), &event.data[0], &event.data[1]);

        EventManager::Get()->FireEvent(event);
    }

    void WindowManager::WindowMaximiseCallback(GLFWwindow *pWnd, int maximised) noexcept {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(pWnd));
        Event event{};
        event.category = Event::Category::Window;
        event.pointer = window;
        event.type = maximised? Event::Type::WindowMaximise:Event::Type::WindowRestore;
        glfwGetWindowSize(window->getWindow(), &event.data[0], &event.data[1]);

        EventManager::Get()->FireEvent(event);
    }


}