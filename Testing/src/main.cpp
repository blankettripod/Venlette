//
// Created by reece on 28/07/22.
//

#include <venlette>

int main() {
    Venlette::Util::Logging::Shutdown(); // should fail
    Venlette::Util::Logging::Init(); // should work
    Venlette::Util::Logging::Init(); // should fail
    VEN_CLIENT_INFO("Test"); // should work
    Venlette::Util::Logging::Shutdown(); // should work
    VEN_CLIENT_INFO("Test"); // should fail
    Venlette::Util::Logging::Init(); // should fail
}