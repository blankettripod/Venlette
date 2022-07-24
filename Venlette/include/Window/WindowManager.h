//
// Created by reece on 24/07/22.
//

#pragma once

namespace Venlette::Window {

class WindowManager {
public:

    WindowManager(const WindowManager&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;

    WindowManager(WindowManager&&) = delete;
    WindowManager& operator=(WindowManager&&) = delete;



private:
    WindowManager() noexcept;
    ~WindowManager() noexcept;

};

} // WindowManager
