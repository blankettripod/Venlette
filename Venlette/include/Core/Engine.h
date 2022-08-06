//
// Created by reece on 28/07/22.
//

#pragma once

#include "Core/common.h"

#include "Application/Application.h"
#include "Core/Events/EventManager.h"

namespace Venlette::Core {

class Engine {
public:
    static VEN_RESULT Init() noexcept;
    static VEN_RESULT Shutdown() noexcept;

    template<class App> static VEN_RESULT UseApplication() noexcept {

        if (!s_isInitialised) {
            VEN_CORE_ERROR("[SYSTEM] Failed to create application: Engine not initialised");
            return VEN_FAILURE;
        }
        VEN_CORE_INFO("[SYSTEM] Creating Application");

        App* app;

        try {
            app = new App;
        } catch (std::bad_alloc& e) {
            VEN_CORE_ERROR("[SYSTEM] Failed to create application: Could not allocate memory");
            return VEN_FAILURE;
        } catch (std::exception& e) {
            VEN_CORE_ERROR("[SYSTEM] Failed to create application: {}", e.what());
            return VEN_FAILURE;
        } catch (std::string& e) {
            VEN_CORE_ERROR("[SYSTEM] Failed to create application: {}", e);
            return VEN_FAILURE;
        }

        VEN_CORE_INFO("[SYSTEM] Created Application");

        if (FAILED(app->run())) {
            VEN_CORE_ERROR("[SYSTEM] Failed to run Application");
        }

        try {
            app->start();
        } catch (std::exception& e) {
            VEN_CORE_ERROR("[SYSTEM] Failed to start application: {}", e.what());
            app->kill();
            return VEN_FAILURE;
        } catch (std::string& e) {
            VEN_CORE_ERROR("[SYSTEM] Failed to start application: {}", e);
            app->kill();
            return VEN_FAILURE;
        }

        std::thread updateThread([app] {
            try {
                while (app->isRunning() && s_isInitialised) {
                    Events::EventManager::PollEvents();
                    app->update();
                }
            } catch (std::exception& e) {
                VEN_CORE_ERROR("[SYSTEM] Failed to run application: {}", e.what());
                app->kill();
            } catch (std::string& e) {
                VEN_CORE_ERROR("[SYSTEM] Failed to run application: {}", e);
                app->kill();
            }
        });

        std::thread renderThread([app] {
            try {
                while (app->isRunning() && s_isInitialised) {
                    app->render();
                }
            } catch (std::exception& e) {
                VEN_CORE_ERROR("[SYSTEM] Failed to run application: {}", e.what());
                app->kill();
            } catch (std::string& e) {
                VEN_CORE_ERROR("[SYSTEM] Failed to run application: {}", e);
                app->kill();
            }
        });

        updateThread.join();
        renderThread.join();

        VEN_CORE_INFO("[SYSTEM] Stopping Application");

        try {
            app->stop();
        } catch (std::exception& e) {
            VEN_CORE_ERROR("[SYSTEM] Failed to stop application: {}", e.what());
            app->kill();
            return VEN_FAILURE;
        } catch (std::string& e) {
            VEN_CORE_ERROR("[SYSTEM] Failed to stop application: {}", e);
            app->kill();
            return VEN_FAILURE;
        }

        app->kill();

        try {
            delete app;
        } catch (std::bad_alloc& e) {
            VEN_CORE_ERROR("[SYSTEM] Failed to create application: Could not free memory");
            return VEN_FAILURE;
        } catch (std::exception& e) {
            VEN_CORE_ERROR("[SYSTEM] Failed to create application: {}", e.what());
            return VEN_FAILURE;
        } catch (std::string& e) {
            VEN_CORE_ERROR("[SYSTEM] Failed to create application: {}", e);
            return VEN_FAILURE;
        }

        VEN_CORE_INFO("[SYSTEM] Destroyed Application");

        return VEN_SUCCESS;
    }

private:
    static bool s_isInitialised;
};

} // Core
