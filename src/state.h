#pragma once

#include "mem.h"
#include "disp.h"
#include "timer.h"
#include "stack.h"

using RegT = uint16_t;
constexpr auto NUM_REGS = 16;
using RegsT = std::array<RegT, NUM_REGS>;

struct State {
  Memory mem;
  Display display;
  RegsT regs;
  RegT pc;
  RegT i;
  StackT stack;
  TimerT delayTimer;
  TimerT soundTimer;
};
