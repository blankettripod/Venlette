//
// Created by reece on 22/07/22.
//

#include "Core/Application/Application.h"
#include <thread>
#include "Core/System.h"

namespace Venlette::Entry {
    Application::Application() {
        System::Init();
    }

    Application::~Application() {
        System::Shutdown();
    }

    void Application::run() noexcept {
        m_isRunning = true;

        this->start();

        std::thread updateThread([this] {
            while (this->isRunning()) update();
        });

        std::thread renderThread([this] {
            while (this->isRunning()) render();
        });

        updateThread.join();
        renderThread.join();

        this->stop();

        System::Shutdown();
    }

    void Application::kill() noexcept {
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