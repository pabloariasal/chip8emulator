#pragma once

#include "opcode.h"
#include "state.h"

// clear the screen
void Inst_00E0(Display& dis);

// jump to address
void Inst_1NNN(Opcode opcode, RegT& pc);

// call subroutine at provided access
void Inst_2NNN(Opcode opcode, StackT& stack, RegT& pc);

// return from subroutine
void Inst_00EE(Opcode opcode, StackT& stack, RegT& pc);

// ---------------------------- Skipping -----------
void Inst_9XY0(Opcode opcode, const RegsT& regs, RegT& pc);

void Inst_5XY0(Opcode opcode, const RegsT& regs, RegT& pc);

void Inst_3XNN(Opcode opcode, const RegsT& regs, RegT& pc);

void Inst_4XNN(Opcode opcode, const RegsT& regs, RegT& pc);

// ---------------------------- Register Generic -----------
void Inst_6XNN(Opcode opcode, RegsT& regs);

void Inst_7XNN(Opcode opcode, RegsT& regs);

// Math/arithmetic
void Inst_8XY0(Opcode opcode, RegsT& regs);

void Inst_8XY1(Opcode opcode, RegsT& regs);
void Inst_8XY2(Opcode opcode, RegsT& regs);
void Inst_8XY3(Opcode opcode, RegsT& regs);
void Inst_8XY4(Opcode opcode, RegsT& regs);
void Inst_8XY5(Opcode opcode, RegsT& regs);
void Inst_8XY7(Opcode opcode, RegsT& regs);
void Inst_8XY6(Opcode opcode, RegsT& regs);
void Inst_8XYE(Opcode opcode, RegsT& regs);

// set index register I to NNN
void Inst_ANNN(Opcode opcode, RegT& i);

// jump with offset (table lookup)
void Inst_BNNN(Opcode opcode, const RegsT& regs, RegT& pc);

// Generate random number
void Inst_CXNN(Opcode opcode, RegsT& regs);

// draw sprite
void Inst_DXYN(Opcode opcode, RegsT& regs, const Memory& mem, const RegT& i,
               Display& dis);

// skip if key is pressed
void Inst_EX9E(Opcode opcode, const RegsT& regs, RegT& pc);

// skip if key is not pressed
void Inst_EXA1(Opcode opcode, const RegsT& regs, RegT& pc);

// read delay timer
void Inst_FX07(Opcode opcode, const TimerT& delay_timer, RegsT& regs);

// set delay timer
void Inst_FX15(Opcode opcode, const RegsT& regs, TimerT& delay_timer);

// set sound timer
void Inst_FX18(Opcode opcode, const RegsT& regs, TimerT& sound_timer);

// Adds to register I
void Inst_FX1E(Opcode opcode, const RegsT& regs, RegT& i);

// get key
void Inst_FX0A(Opcode opcode, RegsT& regs, RegT& pc);

// sets I to font character
void Inst_FX29(Opcode opcode, const RegsT& regs, const Memory& mem, RegT& i);

// stores decimal in memory at location I
void Inst_FX33(Opcode opcode, const RegsT& regs, const RegT& i, Memory& mem);

// write memory
void Inst_FX55(Opcode opcode, const RegsT& regs, const RegT& i, Memory& mem);

// read memory
void Inst_FX65(Opcode opcode, const RegT& i, Memory& mem, RegsT& regs);
