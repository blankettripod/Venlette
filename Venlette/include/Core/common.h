//
// Created by reece on 28/07/22.
//

#pragma once

#include <cstdint>
#include <cstddef>

#include <memory>
#include <vector>
#include <queue>
#include <map>

#include <optional>
#include <thread>
#include <new>

#define VEN_RESULT uint8_t
#define SUCCEEDED(result) (result) == 0
#define FAILED(result) !(SUCCEEDED(result))

#define VEN_SUCCESS (VEN_RESULT)0u
#define VEN_FAILURE (VEN_RESULT)1u

#define END_MACRO static_assert(true)

#include "Util/Logging.h"
