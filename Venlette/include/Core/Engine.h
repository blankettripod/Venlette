//
// Created by reece on 28/07/22.
//

#pragma once
#include "Core/common.h"

namespace Venlette::Core {

class Engine {
public:
    static VEN_RESULT Init() noexcept;
    static VEN_RESULT Shutdown() noexcept;
};

} // Core
