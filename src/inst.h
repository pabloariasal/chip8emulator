#pragma once

#include "opcode.h"
#include "state.h"

// clear the screen
void Inst_00E0(Display& dis);

// jump to address
void Inst_1NNN(Opcode opcode, Memory::Index& pc);

// call subroutine at provided access
void Inst_2NNN(Opcode opcode, StackT& stack, Memory::Index& pc);

// return from subroutine
void Inst_00EE(Opcode opcode, StackT& stack, Memory::Index& pc);

// ---------------------------- Skipping -----------
void Inst_9XY0(Opcode opcode, const RegsT& regs, Memory::Index& pc);

void Inst_5XY0(Opcode opcode, const RegsT& regs, Memory::Index& pc);

void Inst_3XNN(Opcode opcode, const RegsT& regs, Memory::Index& pc);

void Inst_4XNN(Opcode opcode, const RegsT& regs, Memory::Index& pc);

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
void Inst_ANNN(Opcode opcode, Memory::Index& i);

// jump with offset (table lookup)
void Inst_BNNN(Opcode opcode, const RegsT& regs, Memory::Index& pc);

// Generate random number
void Inst_CXNN(Opcode opcode, RegsT& regs);

// draw sprite
void Inst_DXYN(Opcode opcode, RegsT& regs, const Memory& mem,
               const Memory::Index& i, Display& dis);

// skip if key is pressed
void Inst_EX9E(Opcode opcode, const std::optional<KeyT>& key, const RegsT& regs,
               Memory::Index& pc);

// skip if key is not pressed
void Inst_EXA1(Opcode opcode, const std::optional<KeyT>& key, const RegsT& regs,
               Memory::Index& pc);

// read delay timer
void Inst_FX07(Opcode opcode, const Timer& delay_timer, RegsT& regs);

// set delay timer
void Inst_FX15(Opcode opcode, const RegsT& regs, Timer& delay_timer);

// set sound timer
void Inst_FX18(Opcode opcode, const RegsT& regs, Timer& sound_timer);

// Adds to register I
void Inst_FX1E(Opcode opcode, const RegsT& regs, Memory::Index& i);

// get key
void Inst_FX0A(Opcode opcode, const std::optional<KeyT>& key, RegsT& regs,
               Memory::Index& pc);

// sets I to font character
void Inst_FX29(Opcode opcode, const RegsT& regs, Memory::Index& i);

// stores decimal in memory at location I
void Inst_FX33(Opcode opcode, const RegsT& regs, const Memory::Index& i,
               Memory& mem);

// write memory
void Inst_FX55(Opcode opcode, const RegsT& regs, const Memory::Index& i,
               Memory& mem);

// read memory
void Inst_FX65(Opcode opcode, const Memory::Index& i, Memory& mem, RegsT& regs);
