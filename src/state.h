#pragma once

#include "disp.h"
#include "mem.h"
#include "stack.h"
#include "timer.h"

using RegT = uint16_t;
constexpr auto NUM_REGS = 16;
using RegsT = std::array<RegT, NUM_REGS>;

struct State {
  Memory mem;
  Display display;
  RegsT regs;
  RegT pc{Memory::ROM_BEGIN};
  RegT i;
  StackT stack;
  TimerT delayTimer;
  TimerT soundTimer;
};
