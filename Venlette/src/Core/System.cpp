//
// Created by reece on 22/07/22.
//

#include "Core/System.h"
#include "Util/Logging/Logger.h"

namespace Venlette {
void System::Init() noexcept {
    Util::Logger::Init();
}

void System::Shutdown() noexcept {

}
} // Venlette