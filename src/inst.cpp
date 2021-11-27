#include "inst.h"

#include <inttypes.h>

#include <iostream>

#include "display.h"
#include "opcode.h"
#include "state.h"

// clear the screen
void Inst_00E0(Display& dis) { dis.setAll(Color::WHITE); }

// jump to address
void Inst_1NNN(Opcode opcode, RegT& pc) { pc = lastThree(opcode); }

// call subroutine at provided access
void Inst_2NNN(Opcode opcode, StackT& stack, RegT& pc) {
  (void)opcode;
  (void)stack;
  (void)pc;
}

// return from subroutine
void Inst_00EE(Opcode opcode, StackT& stack, RegT& pc) {
  (void)opcode;
  (void)stack;
  (void)pc;
}

// ---------------------------- Skipping -----------
void Inst_9XY0(Opcode opcode, RegT& pc) {
  (void)pc;
  (void)opcode;
}

void Inst_5XY0(Opcode opcode, RegT& pc) {
  (void)pc;
  (void)opcode;
}

void Inst_3XNN(Opcode opcode, const RegsT& regs, RegT& pc) {
  (void)regs;
  (void)pc;
  (void)opcode;
}

void Inst_4XNN(Opcode opcode, const RegsT& regs, RegT& pc) {
  (void)regs;
  (void)pc;
  (void)opcode;
}

// ---------------------------- Register Generic -----------
void Inst_6XNN(Opcode opcode, RegsT& regs) {
  const auto r = second(opcode);
  const auto v = lastTwo(opcode);
  regs[r] = v;
}

void Inst_7XNN(Opcode opcode, RegsT& regs) {
  const auto r = second(opcode);
  const auto v = lastTwo(opcode);
  regs[r] += v;
}

// Math/arithmetic
void Inst_8XY0(Opcode opcode, RegsT& regs) {
  (void)regs;
  (void)opcode;
}

void Inst_8XY1(Opcode opcode, RegsT& regs) {
  (void)regs;
  (void)opcode;
}
void Inst_8XY2(Opcode opcode, RegsT& regs) {
  (void)regs;
  (void)opcode;
}
void Inst_8XY3(Opcode opcode, RegsT& regs) {
  (void)regs;
  (void)opcode;
}
void Inst_8XY4(Opcode opcode, RegsT& regs) {
  (void)regs;
  (void)opcode;
}
void Inst_8XY5(Opcode opcode, RegsT& regs) {
  (void)regs;
  (void)opcode;
}
void Inst_8XY7(Opcode opcode, RegsT& regs) {
  (void)regs;
  (void)opcode;
}
void Inst_8XY6(Opcode opcode, RegsT& regs) {
  (void)regs;
  (void)opcode;
}
void Inst_8XYE(Opcode opcode, RegsT& regs) {
  (void)regs;
  (void)opcode;
}

// set index register I to NNN
void Inst_ANNN(Opcode opcode, RegT& i) { i = lastThree(opcode); }

// jump with offset (table lookup)
void Inst_BNNN(Opcode opcode, const RegsT& regs, RegT& pc) {
  (void)pc;
  (void)regs;
  (void)opcode;
}

// Generate random number
void Inst_CXNN(Opcode opcode, RegsT& regs) {
  (void)regs;
  (void)opcode;
}

// draw sprite
void Inst_DXYN(Opcode opcode, const Memory& mem, const RegT& i, Display& dis) {
  const auto x = second(opcode);
  const auto y = third(opcode);
  const auto n = fourth(opcode);
  drawSprite(x, y, PixelBuffer<Color>(8, toColorVec(readN(mem, i, n))), dis);
}

// skip if key is pressed
void Inst_EX9E(Opcode opcode, const RegsT& regs, RegT& pc) {
  (void)regs;
  (void)pc;
  (void)opcode;
}

// skip if key is not pressed
void Inst_EXA1(Opcode opcode, const RegsT& regs, RegT& pc) {
  (void)regs;
  (void)pc;
  (void)opcode;
}

// read delay timer
void Inst_FX07(Opcode opcode, const TimerT& delay_timer, RegsT& regs) {
  (void)opcode;
  (void)delay_timer;
  (void)regs;
}

// set delay timer
void Inst_FX15(Opcode opcode, const RegsT& regs, TimerT& delay_timer) {
  (void)opcode;
  (void)delay_timer;
  (void)regs;
}

// set sound timer
void Inst_FX18(Opcode opcode, const RegsT& regs, TimerT& sound_timer) {
  (void)opcode;
  (void)sound_timer;
  (void)regs;
}

// Adds to register I
void Inst_FX1E(Opcode opcode, const RegsT& regs, RegT& i) {
  (void)opcode;
  (void)regs;
  (void)i;
}

// get key
void Inst_FX0A(Opcode opcode, RegsT& regs, RegT& pc) {
  (void)opcode;
  (void)regs;
  (void)pc;
}

// sets I to font character
void Inst_FX29(Opcode opcode, const RegsT& regs, const Memory& mem, RegT& i) {
  (void)opcode;
  (void)regs;
  (void)i;
  (void)mem;
}

// stores decimal in memory at location I
void Inst_FX33(Opcode opcode, const RegsT& regs, const RegT& i, Memory& mem) {
  (void)opcode;
  (void)regs;
  (void)i;
  (void)mem;
}

// write memory
void Inst_FX55(Opcode opcode, const RegsT& regs, const RegT& i, Memory& mem) {
  for (int r = 0; r < second(opcode) + 1; ++r) {
    mem.write(i + r, regs[r]);
  }
}

// read memory
void Inst_FX65(Opcode opcode, const RegT& i, Memory& mem, RegsT& regs) {
  for (int r = 0; r < second(opcode) + 1; ++r) {
    regs[r] = mem.read(i + r);
  }
}
