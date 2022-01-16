#include "process_instruction.h"

#include <cassert>

#include "inst.h"
#include "opcode.h"

Opcode nextOpcode(State& state) {
  auto opcode =
      buildOpcode(state.mem.read(state.pc), state.mem.read(state.pc + 1));
  state.pc += OPCODE_SIZE_WORDS;
  return opcode;
}

void processInstruction(Opcode opcode, State& state) {
  switch (first(opcode)) {
    case 0x0:
      if (lastThree(opcode) == 0x0E0) {
        Inst_00E0(state.display);
      } else {
        Inst_00EE(opcode, state.stack, state.pc);
      }
      break;
    case 0x1:
      Inst_1NNN(opcode, state.pc);
      break;
    case 0x2:
      Inst_2NNN(opcode, state.stack, state.pc);
      break;
    case 0x3:
      Inst_3XNN(opcode, state.regs, state.pc);
      break;
    case 0x4:
      Inst_4XNN(opcode, state.regs, state.pc);
      break;
    case 0x5:
      Inst_5XY0(opcode, state.regs, state.pc);
      break;
    case 0x6:
      Inst_6XNN(opcode, state.regs);
      break;
    case 0x7:
      Inst_7XNN(opcode, state.regs);
      break;
    case 0x8:
      switch (fourth(opcode)) {
        case 0x0:
          Inst_8XY0(opcode, state.regs);
          break;
        case 0x1:
          Inst_8XY1(opcode, state.regs);
          break;
        case 0x2:
          Inst_8XY2(opcode, state.regs);
          break;
        case 0x3:
          Inst_8XY3(opcode, state.regs);
          break;
        case 0x4:
          Inst_8XY4(opcode, state.regs);
          break;
        case 0x5:
          Inst_8XY5(opcode, state.regs);
          break;
        case 0x7:
          Inst_8XY7(opcode, state.regs);
          break;
        case 0x6:
          Inst_8XY6(opcode, state.regs);
          break;
        case 0xE:
          Inst_8XYE(opcode, state.regs);
          break;
        default:
          assert(false);
      }
      break;
    case 0x9:
      Inst_9XY0(opcode, state.regs, state.pc);
      break;
    case 0xA:
      Inst_ANNN(opcode, state.i);
      break;
    case 0xB:
      Inst_BNNN(opcode, state.regs, state.pc);
      break;
    case 0xC:
      Inst_CXNN(opcode, state.regs);
      break;
    case 0xD:
      Inst_DXYN(opcode, state.regs, state.mem, state.i, state.display);
      break;
    case 0xE:
      switch (lastTwo(opcode)) {
        case 0x9E:
          Inst_EX9E(opcode, state.key, state.regs, state.pc);
          break;
        case 0xA1:
          Inst_EXA1(opcode, state.key, state.regs, state.pc);
          break;
        default:
          assert(false);
      }
      break;
    case 0xF:
      switch (lastTwo(opcode)) {
        case 0x55:
          Inst_FX55(opcode, state.regs, state.i, state.mem);
          break;
        case 0x65:
          Inst_FX65(opcode, state.i, state.mem, state.regs);
          break;
        case 0x0A:
          Inst_FX0A(opcode, state.key, state.regs, state.pc);
          break;
        case 0x29:
          Inst_FX29(opcode, state.regs, state.i);
          break;
        case 0x33:
          Inst_FX33(opcode, state.regs, state.i, state.mem);
          break;
        case 0x1E:
          Inst_FX1E(opcode, state.regs, state.i);
          break;
        case 0x07:
          Inst_FX07(opcode, state.delayTimer, state.regs);
          break;
        case 0x15:
          Inst_FX15(opcode, state.regs, state.delayTimer);
          break;
        case 0x18:
          Inst_FX18(opcode, state.regs, state.soundTimer);
          break;
        default:
          assert(false);
      }
      break;
    default:
      assert(false);
  }
}
