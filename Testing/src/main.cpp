//
// Created by reece on 28/07/22.
//

#include <venlette>

class App : public Venlette::Application::Application, public Venlette::Events::IEventListener {
public:
    App() = default;
    ~App() override = default;

    void start() override {
    }

    void update() override {
        static int runs=5;
        VEN_CLIENT_INFO("Runs Left: {}", runs);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (!--runs) kill();
    }

    void render() override {
    }

    bool OnEvent(const Venlette::Events::Event& event) noexcept override{
        VEN_CLIENT_INFO("Event Received");

        return false;
    }

    void stop() override {
        VEN_CLIENT_INFO("Application Stopping");
    }
};

int main() {
    if (FAILED(Venlette::Core::Engine::Init())) throw std::runtime_error("Failed to initialise engine");
    Venlette::Core::Engine::UseApplication<App>();
    if (FAILED(Venlette::Core::Engine::Shutdown())) throw std::runtime_error("Failed to shutdown engine");

    return 0;
}