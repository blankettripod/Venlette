//
// Created by reece on 20/07/22.
//

#include <venlette>
#include <thread>
#include <iostream>

class TestEvents : public Venlette::Events::IEventListener {
public:
    bool OnEvent(const Venlette::Events::Event& event) noexcept override {
        VEN_CLIENT_INFO("Event received: {}", (signed)event.type);
        return false;
    }
};

class App : public Venlette::Entry::Application, public TestEvents {
protected:
    void start() override {

    }

    void update() override {
        Venlette::Events::EventManager::Get()->PollEvents();
        static int runs = 5;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (--runs == 0) {
            kill();
        }
        VEN_CLIENT_INFO("Hello World!");
    }
};


int main() {
    App* app = new App;
    app->run();

    while (app->isRunning());

}