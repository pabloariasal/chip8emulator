#pragma once

#include <stack>

#include "mem.h"
#include "disp.h"
#include "regs.h"
#include "timer.h"
#include "stack.h"

struct State {
  Memory mem;
  Display display;
  Memory::Index pc;
  Memory::Index i;
  Regs regs;
  Stack<Memory::Index> stack;
  TimerT delayTimer;
  TimerT soundTimer;
};
