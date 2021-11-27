#pragma once

#include "mem.h"
#include "disp.h"
#include "regs.h"
#include "timer.h"
#include "stack.h"

struct State {
  Memory mem;
  Display display;
  Regs regs;
  RegT pc;
  RegT i;
  StackT stack;
  TimerT delayTimer;
  TimerT soundTimer;
};
