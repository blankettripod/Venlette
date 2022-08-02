//
// Created by reece on 30/07/22.
//

#pragma once

#include "Core/common.h"
#include "Core/Engine.h"


namespace Venlette::Application {

class Application {
public:
    Application() noexcept = default;    // should only initialise member variables
    virtual ~Application() noexcept = default; // should only destroy heap member variables

    [[nodiscard]] bool isRunning() const noexcept;

    virtual VEN_RESULT run() noexcept final; // should not be overridden by client
    virtual VEN_RESULT kill() noexcept final; // should not be overridden by client

    virtual void start() {}; // called when the application has been initialised (does not start app)
    virtual void stop() {};  // called when application is about to be shutdown  (does not stop app)

    virtual void update() {};
    virtual void render() {};

private:
    bool m_isRunning = false;
};

} // Application
