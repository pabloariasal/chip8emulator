#pragma once

#include <inttypes.h>

using RegT = uint16_t;
constexpr auto NUM_REGS = 16;

using Regs = RegT[NUM_REGS];
