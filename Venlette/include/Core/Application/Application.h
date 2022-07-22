//
// Created by reece on 22/07/22.
//

#pragma once

namespace Venlette::Entry {

class Application {
public:
    Application();
    virtual ~Application();

    virtual void run() noexcept final; // called by client
    virtual void kill() noexcept final;

    [[nodiscard]] virtual bool isRunning() const noexcept final;
protected:
    virtual void start(); // called by engine
    virtual void stop(); // called after application is closed, NOT used to close the application

private:
    virtual void update();
    virtual void render();

    volatile bool m_isRunning{};
};

} // Entry
