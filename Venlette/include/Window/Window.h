//
// Created by reece on 24/07/22.
//

#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <string_view>
#include "Core/Events/IEventListener.h"

namespace Venlette::Window {

class Window : public Events::IEventListener {
public:
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

    struct WindowInfo {
         std::string title = "Venlette Window";

         using Resolution = struct {signed width, height;};
         Resolution windowedSize   {640, 480};
         Resolution fullscreenSize {1920, 1080};

         bool resizable {false};
         bool decorated  {true};

         struct {
             bool windowed   {true};
             bool borderless {true};
             bool fullscreen {true};
         } enabledModes;
         unsigned defaultMode {0};

         struct {unsigned red   {8}; unsigned blue  {8};
                 unsigned green {8}; unsigned alpha {8};} bitDepth;
         signed refreshRate {-1};
    };

    explicit Window(const WindowInfo &info) noexcept;
    ~Window() noexcept override;

    [[nodiscard]] std::string_view getTitle() const noexcept;

    [[nodiscard]] WindowInfo::Resolution getWindowedResolution() const noexcept;
    [[nodiscard]] WindowInfo::Resolution getFullscreenResolution() const noexcept;
    [[nodiscard]] WindowInfo::Resolution getCurrentResolution() const noexcept;

    [[nodiscard]] bool getResizable() const noexcept;
    [[nodiscard]] bool getDecorated() const noexcept;

    [[nodiscard]] bool getModeEnabled(unsigned mode) const noexcept;
    [[nodiscard]] unsigned getMode() const noexcept;

    [[nodiscard]] const signed* getBitDepth() const noexcept;
    [[nodiscard]] signed getRefreshRate() const noexcept;

    [[nodiscard]] bool isOpen() const noexcept;

    [[nodiscard]] GLFWwindow* getWindow() const noexcept;


    void setTitle(const std::string& title) noexcept;

    void setWindowedResolution(const WindowInfo::Resolution& resolution) noexcept;
    void setFullscreenResolution(const WindowInfo::Resolution& resolution) noexcept;
    void setCurrentResolution(const WindowInfo::Resolution& resolution) noexcept;

    void setResizable(bool resizeable)  noexcept;
    void setDecorated(bool decorated) noexcept;

    void setModeEnabled(unsigned mode, bool enabled) noexcept;
    bool setMode(unsigned mode) noexcept;

    void setBitDepth(const unsigned* bitDepth) noexcept;
    void setRefreshRate(signed refreshRate) noexcept;

    bool OnEvent(const Events::Event& event) noexcept override;

    void close() noexcept;


private:

    void destroy() noexcept;

    WindowInfo m_info {};
    WindowInfo::Resolution defaultFullscreenResolution {};

    GLFWwindow* m_pWnd {nullptr};

    bool m_isOpen = false;
    signed m_closeReason = 0; // 0 = destructor, 1 = manual
};

} // Window
