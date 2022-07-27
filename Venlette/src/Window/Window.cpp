//
// Created by reece on 24/07/22.
//

#include "Window/Window.h"
#include "Core/common.h"
#include "Core/Events/Event.h"
#include "Core/Events/EventManager.h"
#include "Window/WindowManager.h"


namespace Venlette::Window {
    using namespace Events;

    Window::Window(const WindowInfo &info) noexcept {

        VEN_CORE_INFO("[WINDOW] Creating Window \"{}\"", info.title);

        // Get the monitor count
        signed monitorCount;
        {[[gnu::unused]] auto _ = glfwGetMonitors(&monitorCount);}

        if (monitorCount == 0) {
            VEN_CORE_ERROR("[WINDOW] Cannot Create Window \"{}\": No monitors connected", info.title);
            return;
        }

        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

        // get the fullscreen resolution for if the default was chosen
        signed defaultWidth = videoMode->width;
        signed defaultHeight = videoMode->height;

        // choose the fullscreen resolution
        signed fullWidth = info.fullscreenSize.width == -1?
                           defaultWidth:info.fullscreenSize.width;
        signed fullHeight = info.fullscreenSize.height == -1?
                           defaultHeight:info.fullscreenSize.height;

        // choose the final resolution based on window mode
        signed finalWidth = info.defaultMode == 0?
                info.windowedSize.width:fullWidth;
        signed finalHeight = info.defaultMode == 0?
                info.windowedSize.height:fullHeight;

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, info.resizable);
        glfwWindowHint(GLFW_DECORATED, info.decorated && (info.defaultMode==0));

        GLFWwindow* pWnd = glfwCreateWindow(finalWidth, finalHeight, info.title.c_str(),
                                            info.defaultMode==2? primaryMonitor:nullptr, nullptr);

        if (!pWnd) {
            VEN_CORE_ERROR("[WINDOW] Failed to create window \"{}\": unknown glfw error", info.title);
            return;
        }

        glfwSetWindowUserPointer(pWnd, this);
        glfwSetWindowPosCallback(pWnd, WindowManager::WindowPositionCallback);
        glfwSetWindowSizeCallback(pWnd, WindowManager::WindowResizeCallback);
        glfwSetWindowCloseCallback(pWnd, WindowManager::WindowCloseCallback);
        glfwSetWindowFocusCallback(pWnd, WindowManager::WindowFocusCallback);
        glfwSetWindowIconifyCallback(pWnd, WindowManager::WindowMinimiseCallback);
        glfwSetWindowMaximizeCallback(pWnd, WindowManager::WindowMaximiseCallback);

        m_pWnd = pWnd;
        m_info = info;

        if (m_info.refreshRate == -1) {
            m_info.refreshRate = videoMode->refreshRate;
        }

        defaultFullscreenResolution = {fullWidth, fullHeight};

        m_isOpen = true;
        VEN_CORE_INFO("[WINDOW] Created window \"{}\"", info.title);
    }

    Window::~Window() noexcept {
        if (!m_pWnd && m_closeReason==0) {
            VEN_CORE_ERROR("[WINDOW] Failed to destroy window \"{}\": Window doesn't exist", m_info.title);
            return;
        }

        glfwDestroyWindow(m_pWnd);
        m_pWnd = nullptr;
    }

    std::string_view Window::getTitle() const noexcept {
        return m_info.title;
    }

    Window::WindowInfo::Resolution Window::getWindowedResolution() const noexcept {
        return m_info.windowedSize;
    }

    Window::WindowInfo::Resolution Window::getFullscreenResolution() const noexcept {
        return m_info.fullscreenSize;
    }

    Window::WindowInfo::Resolution Window::getCurrentResolution() const noexcept {
        return m_info.defaultMode==0? m_info.windowedSize:m_info.fullscreenSize;
    }

    bool Window::getResizable() const noexcept {
        return m_info.resizable;
    }

    bool Window::getDecorated() const noexcept {
        return m_info.decorated;
    }

    bool Window::getModeEnabled(unsigned mode) const noexcept {
        switch (mode) {
            case 0:
                return m_info.enabledModes.windowed;
            case 1:
                return m_info.enabledModes.borderless;
            case 2:
                return m_info.enabledModes.fullscreen;
            default:
                VEN_CORE_ERROR("[WINDOW] Cannot get status of mode {}: mode doesn't exist");
                return false;
        }
    }

    unsigned Window::getMode() const noexcept {
        return m_info.defaultMode;
    }

    const signed *Window::getBitDepth() const noexcept {
        return reinterpret_cast<const signed *>(&m_info.bitDepth);
    }

    signed Window::getRefreshRate() const noexcept {
        return m_info.refreshRate;
    }

    void Window::setTitle(const std::string &title) noexcept {
        if (!m_pWnd) {
            VEN_CORE_ERROR("[WINDOW] Cannot set title of window\"{}\": Window doesn't exist", m_info.title);
            return;
        }
        m_info.title = title;
        glfwSetWindowTitle(m_pWnd, title.c_str());
    }

    void Window::setWindowedResolution(const WindowInfo::Resolution &resolution) noexcept {
        if (!m_pWnd) {
            VEN_CORE_ERROR("[WINDOW] Cannot set windowed size of window \"{}\": Window doesn't exist", m_info.title);
            return;
        }
        m_info.windowedSize = resolution;
        if (m_info.defaultMode == 0) {
            glfwSetWindowSize(m_pWnd, resolution.width, resolution.height);
        }
    }

    void Window::setFullscreenResolution(const WindowInfo::Resolution &resolution) noexcept {
        if (!m_pWnd) {
            VEN_CORE_ERROR("[WINDOW] Cannot set fullscreen size of window \"{}\": Window doesn't exist", m_info.title);
            return;
        }
        WindowInfo::Resolution final = {
                resolution.width==-1? defaultFullscreenResolution.width:resolution.width,
                resolution.height==-1? defaultFullscreenResolution.height:resolution.height,
        };

        m_info.fullscreenSize = final;
        if (m_info.defaultMode == 1 || m_info.defaultMode == 2) {
            glfwSetWindowSize(m_pWnd, resolution.width, resolution.height);
        }
    }

    void Window::setCurrentResolution(const Window::WindowInfo::Resolution &resolution) noexcept {
        if (!m_pWnd) {
            VEN_CORE_ERROR("[WINDOW] Cannot set size of window \"{}\": Window doesn't exist", m_info.title);
            return;
        }
        if (m_info.decorated == 0) {
            setWindowedResolution(resolution);
        } else {
            setFullscreenResolution(resolution);
        }
    }

    void Window::setResizable(bool resizable) noexcept {
        if (!m_pWnd) {
            VEN_CORE_ERROR("[WINDOW] Cannot set resizable of window \"{}\": Window doesn't exist", m_info.title);
            return;
        }
        m_info.resizable = resizable;
        glfwSetWindowAttrib(m_pWnd, GLFW_RESIZABLE, resizable);
    }

    void Window::setDecorated(bool decorated) noexcept {
        if (!m_pWnd) {
            VEN_CORE_ERROR("[WINDOW] Cannot set decorated of window \"{}\": Window doesn't exist", m_info.title);
            return;
        }
        m_info.decorated = decorated;
        glfwSetWindowAttrib(m_pWnd, GLFW_DECORATED, decorated);
    }

    void Window::setModeEnabled(unsigned mode, bool enabled) noexcept {
        switch (mode) {
            case 0:
                m_info.enabledModes.windowed = enabled;
                break;
            case 1:
                m_info.enabledModes.borderless = enabled;
                break;
            case 2:
                m_info.enabledModes.fullscreen = enabled;
                break;
            default:
                VEN_CORE_ERROR("[WINDOW] Cannot set status of mode {}: Mode doesn't exist");
                break;
        }
    }

    bool Window::setMode(unsigned mode) noexcept {
        if (!m_pWnd) {
            VEN_CORE_ERROR("[WINDOW] Cannot set mode of window \"{}\": Window doesn't exist", m_info.title);
            return false;
        }
        if (mode < 0u || mode > 2u) {
            VEN_CORE_ERROR("[WINDOW] Cannot set window \"{}\" to mode {}: Mode doesn't exist", m_info.title, mode);
            return false;
        }
        if (!getModeEnabled(mode)) {
            VEN_CORE_ERROR("[WINDOW] Cannot set window \"{}\" to mode {}: Mode is not enabled", m_info.title, mode);
        }

        m_info.defaultMode = mode;
        switch (mode) {
            case 0: // windowed
                glfwSetWindowMonitor(m_pWnd, nullptr, GLFW_DONT_CARE, GLFW_DONT_CARE,
                                     m_info.windowedSize.width, m_info.windowedSize.height,
                                     GLFW_DONT_CARE);
                glfwSetWindowAttrib(m_pWnd, GLFW_DECORATED, m_info.decorated);
                glfwSetWindowAttrib(m_pWnd, GLFW_RESIZABLE, m_info.resizable);
                return true;

            case 1:
                // TODO: make sure that borderless uses the position of the main window
                //  (encase the main monitor is not to the very left)
                glfwSetWindowMonitor(m_pWnd, nullptr, 0, 0,
                                     m_info.fullscreenSize.width, m_info.fullscreenSize.height,
                                     GLFW_DONT_CARE);
                glfwSetWindowAttrib(m_pWnd, GLFW_DECORATED, GLFW_FALSE);
                glfwSetWindowAttrib(m_pWnd, GLFW_RESIZABLE, GLFW_FALSE);
                return true;

            case 2:
                glfwSetWindowMonitor(m_pWnd, glfwGetPrimaryMonitor(), 0, 0,
                                     m_info.fullscreenSize.width, m_info.fullscreenSize.height,
                                     m_info.refreshRate);
                glfwSetWindowAttrib(m_pWnd, GLFW_DECORATED, GLFW_FALSE);
                glfwSetWindowAttrib(m_pWnd, GLFW_RESIZABLE, GLFW_FALSE);
                return true;

            default:
                VEN_CORE_ERROR("[WINDOW] Cannot set mode of window \"{}\" to mode {}: Mode doesn't exist", m_info.title, mode);
                return false;


        }
    }

    void Window::setBitDepth(const unsigned *bitDepth) noexcept {
        memcpy(&m_info.bitDepth, bitDepth, sizeof(unsigned[4]));
    }

    void Window::setRefreshRate(signed refreshRate) noexcept {
        m_info.refreshRate = refreshRate;
    }

    bool Window::OnEvent(const Events::Event &event) noexcept {

        using Type = Event::Type;

        if (event.pointer != this) return false;
        switch (event.type) {
            case Type::WindowClose:
                destroy();
                break;
            case Type::WindowMove:
                break;
            case Type::WindowResize:
                setCurrentResolution({event.data[0], event.data[1]});
                break;
            case Type::WindowGainFocus:
            case Type::WindowLoseFocus:
                break;
            case Type::WindowMaximise:
            case Type::WindowMinimise:
            case Type::WindowRestore:
                setCurrentResolution({event.data[0], event.data[1]});
                break;
            default:
                return false;
        }

        return true;
    }

    bool Window::isOpen() const noexcept {
        return m_isOpen;
    }

    void Window::close() noexcept {
        if (!m_pWnd) {
            VEN_CORE_ERROR("[WINDOW] Cannot destroy window \"{}\": Window doesn't exist", m_info.title);
            return;
        }

        glfwSetWindowShouldClose(m_pWnd, true);

    }

    void Window::destroy() noexcept {
        VEN_CORE_INFO("[WINDOW] Closing Window \"{}\"", m_info.title);
        glfwDestroyWindow(m_pWnd);
        m_isOpen = false;
        m_pWnd = nullptr;
        m_closeReason = 1;
    }

    GLFWwindow *Window::getWindow() const noexcept {
        return m_pWnd;
    }


} // Window