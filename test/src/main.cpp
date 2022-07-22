//
// Created by reece on 20/07/22.
//

#include <venlette>
#include <thread>
#include <iostream>

class App : public Venlette::Entry::Application {
protected:
    void update() override {
        static int runs = 5;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (--runs == 0) {
            kill();
        }
        VEN_CORE_ERROR("Hello World!");
    }
};

int main() {
    App* app = new App;
    app->run();

    while (app->isRunning());

}