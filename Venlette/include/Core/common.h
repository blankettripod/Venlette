//
// Created by reece on 28/07/22.
//

#pragma once

#include <cstdint>
#include <cstddef>

#define VEN_RESULT uint8_t
#define SUCCEEDED(result) (result) == 0
#define FAILED(result) !(SUCCEEDED(result))

#define VEN_SUCCESS (VEN_RESULT)0u
#define VEN_FAILURE (VEN_RESULT)1u

#include "Util/Logging.h"
