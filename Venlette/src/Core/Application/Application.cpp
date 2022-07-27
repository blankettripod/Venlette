//
// Created by reece on 22/07/22.
//

#include <thread>
#include "Core/System.h"
#include "Core/Application/Application.h"
#include "Core/common.h"
#include "Core/Events/EventManager.h"
#include "Window/WindowManager.h"

namespace Venlette::Entry {
    Application::Application() {
        System::Init();
    }

    Application::~Application() {
        System::Shutdown();
    }

    void Application::run() noexcept {

        if (m_isRunning) {
            VEN_CORE_ERROR("[APPLICATION] Cannot start: Already running");
            return;
        }

        m_isRunning = true;
        VEN_CORE_INFO("[APPLICATION] Starting");
        this->start();

        std::thread updateThread([this] {
            while (this->isRunning()) {
                Events::EventManager::Get()->PollEvents();
                update();
            }
        });

        std::thread renderThread([this] {
            while (this->isRunning()) render();
        });

        VEN_CORE_INFO("[APPLICATION] Started");

        updateThread.join();
        renderThread.join();

        VEN_CORE_INFO("[APPLICATION] Stopping");
        this->stop();
        VEN_CORE_INFO("[APPLICATION] Stopped");

    }

    void Application::kill() noexcept {
        m_isRunning = false;
    }

    /* Default Client Functions */
    void Application::start() {
    }

    void Application::stop() {
    }

    void Application::update() {
    }

    void Application::render() {
    }
    /* End Default Client Functions */



    bool Application::isRunning() const noexcept {
        return m_isRunning;
    }
} // Entry