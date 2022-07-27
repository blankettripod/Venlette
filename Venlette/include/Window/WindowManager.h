//
// Created by reece on 24/07/22.
//

#pragma once

#include "Window/Window.h"
#include "Window.h"
#include <string_view>
#include <vector>

namespace Venlette::Window {

class Window;

class WindowManager {
public:

    WindowManager(const WindowManager&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;

    WindowManager(WindowManager&&) = delete;
    WindowManager& operator=(WindowManager&&) = delete;

    static int Init() noexcept;
    static void Shutdown() noexcept;

    static void ErrorCallback(int code, const char* description) noexcept;
    static WindowManager* Get() noexcept;

    static void WindowPositionCallback(GLFWwindow* pWnd, signed x, signed y) noexcept;
    static void WindowResizeCallback(GLFWwindow* pWnd, signed width, signed height) noexcept;
    static void WindowCloseCallback(GLFWwindow* pWnd) noexcept;
    static void WindowFocusCallback(GLFWwindow* pWnd, signed focused) noexcept;
    static void WindowMinimiseCallback(GLFWwindow* pWnd, int minimised) noexcept;
    static void WindowMaximiseCallback(GLFWwindow* pWnd, int maximised) noexcept;

private:
    WindowManager() noexcept;
    ~WindowManager() noexcept;

    static WindowManager* s_instance;

};



} // WindowManager
