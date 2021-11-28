#pragma once

#include <array>

#include "disp.h"
#include "mem.h"
#include "stack.h"
#include "timer.h"

// TODO: move to own header?
using RegT = uint8_t;
constexpr auto NUM_REGS = 16;
using RegsT = std::array<RegT, NUM_REGS>;

struct State {
  Memory mem;
  Display display;
  RegsT regs;
  Memory::Index pc{Memory::ROM_BEGIN};
  Memory::Index i;
  StackT stack;
  TimerT delayTimer;
  TimerT soundTimer;
};
