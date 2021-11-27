#pragma once

#include <inttypes.h>

#include "state.h"

using Opcode = uint16_t;

// clear the screen
void Inst_00E0(Display& dis) { (void)dis; }

// jump to address
void Inst_1NNN(Opcode opcode, RegT& pc) {
  (void)pc;
  (void)opcode;
}

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

void Inst_3XNN(Opcode opcode, const Regs& regs, RegT& pc) {
  (void)regs;
  (void)pc;
  (void)opcode;
}

void Inst_4XNN(Opcode opcode, const Regs& regs, RegT& pc) {
  (void)regs;
  (void)pc;
  (void)opcode;
}

// ---------------------------- Register Generic -----------
void Inst_6XNN(Opcode opcode, Regs& regs) {
  (void)regs;
  (void)opcode;
}

void Inst_7XNN(Opcode opcode, Regs& regs) {
  (void)regs;
  (void)opcode;
}

// Math/arithmetic
void Inst_8XY0(Opcode opcode, Regs& regs) {
  (void)regs;
  (void)opcode;
}

void Inst_8XY1(Opcode opcode, Regs& regs) {
  (void)regs;
  (void)opcode;
}
void Inst_8XY2(Opcode opcode, Regs& regs) {
  (void)regs;
  (void)opcode;
}
void Inst_8XY3(Opcode opcode, Regs& regs) {
  (void)regs;
  (void)opcode;
}
void Inst_8XY4(Opcode opcode, Regs& regs) {
  (void)regs;
  (void)opcode;
}
void Inst_8XY5(Opcode opcode, Regs& regs) {
  (void)regs;
  (void)opcode;
}
void Inst_8XY7(Opcode opcode, Regs& regs) {
  (void)regs;
  (void)opcode;
}
void Inst_8XY6(Opcode opcode, Regs& regs) {
  (void)regs;
  (void)opcode;
}
void Inst_8XYE(Opcode opcode, Regs& regs) {
  (void)regs;
  (void)opcode;
}

// set index register I to NNN
void Inst_ANNN(Opcode opcode, RegT& i) {
  (void)i;
  (void)opcode;
}

// jump with offset (table lookup)
void Inst_BNNN(Opcode opcode, const Regs& regs, RegT& pc) {
  (void)pc;
  (void)regs;
  (void)opcode;
}

// Generate random number
void Inst_CXNN(Opcode opcode, Regs& regs) {
  (void)regs;
  (void)opcode;
}

// draw sprite
void Inst_DXYN(Opcode opcode, Display& dis) {
  (void)opcode;
  (void)dis;
}

// skip if key is pressed
void Inst_EX9E(Opcode opcode, const Regs& regs, RegT& pc) {
  (void)regs;
  (void)pc;
  (void)opcode;
}

// skip if key is not pressed
void Inst_EXA1(Opcode opcode, const Regs& regs, RegT& pc) {
  (void)regs;
  (void)pc;
  (void)opcode;
}

// read delay timer
void Inst_FX07(Opcode opcode, const TimerT& delay_timer, Regs& regs) {
  (void)opcode;
  (void)delay_timer;
  (void)regs;
}

// set delay timer
void Inst_FX15(Opcode opcode, const Regs& regs, TimerT& delay_timer) {
  (void)opcode;
  (void)delay_timer;
  (void)regs;
}

// set sound timer
void Inst_FX18(Opcode opcode, const Regs& regs, TimerT& sound_timer) {
  (void)opcode;
  (void)sound_timer;
  (void)regs;
}

// Adds to register I
void Inst_FX1E(Opcode opcode, const Regs& regs, RegT& i) {
  (void)opcode;
  (void)regs;
  (void)i;
}

// get key
void Inst_FX0A(Opcode opcode, Regs& regs, RegT& pc) {
  (void)opcode;
  (void)regs;
  (void)pc;
}

// sets I to font character
void Inst_FX29(Opcode opcode, const Regs& regs, const Memory& mem,
               RegT& i) {
  (void)opcode;
  (void)regs;
  (void)i;
  (void)mem;
}

// stores decimal in memory at location I
void Inst_FX33(Opcode opcode, const Regs& regs, const RegT& i,
               Memory& mem) {
  (void)opcode;
  (void)regs;
  (void)i;
  (void)mem;
}

// store memmory
void Inst_FX55(Opcode opcode, const Regs& regs, const RegT& i,
               Memory& mem) {
  (void)opcode;
  (void)regs;
  (void)i;
  (void)mem;
}

// read memory
void Inst_FX65(Opcode opcode, const RegT& i, Memory& mem, Regs& regs) {
  (void)opcode;
  (void)regs;
  (void)i;
  (void)mem;
}
