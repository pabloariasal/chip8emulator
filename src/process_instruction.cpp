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
      Inst_00E0(state.display);
      break;
    case 0x1:
      Inst_1NNN(opcode, state.pc);
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
    case 0x9:
      Inst_9XY0(opcode, state.regs, state.pc);
      break;
    case 0xA:
      Inst_ANNN(opcode, state.i);
      break;
    case 0xD:
      Inst_DXYN(opcode, state.regs, state.mem, state.i, state.display);
      break;
    case 0xF:
      if (lastTwo(opcode) == 0x55) {
        Inst_FX55(opcode, state.regs, state.i, state.mem);
      } else {
        Inst_FX65(opcode, state.i, state.mem, state.regs);
      }
      break;
    default:
      assert(false);
  }
}
