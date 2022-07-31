//
// Created by reece on 28/07/22.
//

#include <venlette>

class App : public Venlette::Application::Application {
public:
    App() = default;
    ~App() override = default;

    void start() override {
        VEN_CLIENT_INFO("Application Message");
    }

    void update() override {
        static int runs=5;
        VEN_CLIENT_INFO("Runs Left: {}", runs);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (!--runs) kill();
    }
};

int main() {
    if (FAILED(Venlette::Core::Engine::Init())) throw std::runtime_error("Failed to initialise engine");
    Venlette::Core::Engine::UseApplication<App>();

}