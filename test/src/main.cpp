//
// Created by reece on 20/07/22.
//

#include <venlette>
#include <thread>
#include <iostream>



class App : public Venlette::Entry::Application, public Venlette::Events::IEventListener {
protected:
    void start() override {
        Venlette::Window::Window::WindowInfo windowInfo{};

        windowInfo.enabledModes.windowed = true;
        windowInfo.enabledModes.borderless = true;
        windowInfo.enabledModes.fullscreen = false;

        m_pWnd = new Venlette::Window::Window(windowInfo);


    }

    void stop() override {
        delete m_pWnd;
    }

    void update() override {
        glfwPollEvents();

        if (!m_pWnd->isOpen()) kill();
    }

    bool OnEvent(const Venlette::Events::Event& event) noexcept override {
        VEN_CLIENT_INFO("Event received: {}", (signed)event.type);
        return false;
    }

    signed runs = 5;
    Venlette::Window::Window* m_pWnd{};
};


int main() {
    App* app = new App;

    app->run();

    delete app;

}