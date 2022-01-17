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

using KeyT = uint8_t;
constexpr auto NUM_KEYS = 16;
using KeysT = std::array<bool, NUM_KEYS>;

struct State {
  Memory mem;
  Display display;
  RegsT regs;
  Memory::Index pc{Memory::ROM_BEGIN};
  Memory::Index i;
  StackT stack;
  Timer delayTimer{};
  Timer soundTimer{};
  KeysT keys{};
};
