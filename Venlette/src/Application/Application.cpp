//
// Created by reece on 22/07/22.
//

#include "Application/Application.h"
#include "Core/common.h"
#include <thread>

namespace Venlette::Entry {
    Application::Application() {

    }

    Application::~Application() {

    }

    void Application::run() {
        m_isRunning = true;

        std::thread updateThread([this] {
            while (this->isRunning()) update();
        });

        std::thread renderThread([this] {
            while (this->isRunning()) render();
        });

        updateThread.detach();
        renderThread.detach();
    }

    void Application::kill() {
        m_isRunning = false;
    }

    void Application::start() {

    }

    void Application::stop() {

    }

    void Application::update() {

    }

    void Application::render() {

    }

    bool Application::isRunning() const noexcept {
        return m_isRunning;
    }
} // Entry