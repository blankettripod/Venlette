//
// Created by reece on 30/07/22.
//

#pragma once
#include "Core/common.h"
#include "Application/ApplicationManager.h"

namespace Venlette::Application {

class Application {
public:
    Application() noexcept = default;    // should only initialise member variables
    virtual ~Application() noexcept = 0; // should only destroy heap member variables

    [[nodiscard]] bool isRunning() const noexcept;

protected:
    friend class ::Venlette::Application::ApplicationManager;

    virtual VEN_RESULT run() noexcept final; // should not be overridden by client
    virtual VEN_RESULT kill() noexcept final; // should not be overridden by client

    virtual void start() noexcept = 0; // called when the application has been initialised (does not start app)
    virtual void stop() noexcept = 0;  // called when application is about to be shutdown  (does not stop app)

private:
    virtual void update() noexcept = 0;
    virtual void render() noexcept = 0;

    bool m_isRunning = false;
};

} // Application
