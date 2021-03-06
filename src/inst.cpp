#include "inst.h"

#include <inttypes.h>

#include <random>

#include "draw_sprite.h"
#include "opcode.h"
#include "state.h"

// clear the screen
void Inst_00E0(Display& dis) { dis.setAll(Color::WHITE); }

// jump to address
void Inst_1NNN(Opcode opcode, Memory::Index& pc) { pc = lastThree(opcode); }

// call subroutine at provided access
void Inst_2NNN(Opcode opcode, StackT& stack, Memory::Index& pc) {
  stack.push(pc);
  pc = lastThree(opcode);
}

// return from subroutine
void Inst_00EE(Opcode, StackT& stack, Memory::Index& pc) {
  pc = stack.top();
  stack.pop();
}

// ---------------------------- Skipping -----------
void Inst_9XY0(Opcode opcode, const RegsT& regs, Memory::Index& pc) {
  auto first = second(opcode);
  auto second = third(opcode);

  if (regs.at(first) != regs.at(second)) {
    pc += OPCODE_SIZE_WORDS;
  }
}

void Inst_5XY0(Opcode opcode, const RegsT& regs, Memory::Index& pc) {
  auto first = second(opcode);
  auto second = third(opcode);

  if (regs.at(first) == regs.at(second)) {
    pc += OPCODE_SIZE_WORDS;
  }
}

void Inst_3XNN(Opcode opcode, const RegsT& regs, Memory::Index& pc) {
  auto r = second(opcode);
  auto v = lastTwo(opcode);
  if (v == regs.at(r)) {
    pc += OPCODE_SIZE_WORDS;
  }
}

void Inst_4XNN(Opcode opcode, const RegsT& regs, Memory::Index& pc) {
  auto r = second(opcode);
  auto v = lastTwo(opcode);
  if (v != regs.at(r)) {
    pc += OPCODE_SIZE_WORDS;
  }
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
  auto from = third(opcode);
  auto to = second(opcode);
  regs[to] = regs.at(from);
}

void Inst_8XY1(Opcode opcode, RegsT& regs) {
  auto from = third(opcode);
  auto to = second(opcode);
  regs[to] |= regs.at(from);
}

void Inst_8XY2(Opcode opcode, RegsT& regs) {
  auto from = third(opcode);
  auto to = second(opcode);
  regs[to] &= regs.at(from);
}

void Inst_8XY3(Opcode opcode, RegsT& regs) {
  auto from = third(opcode);
  auto to = second(opcode);
  regs[to] ^= regs.at(from);
}

void Inst_8XY4(Opcode opcode, RegsT& regs) {
  auto from = third(opcode);
  auto to = second(opcode);
  regs[0xF] = 0;
  if (static_cast<unsigned>(regs.at(to) + regs.at(from)) > 0xFF) {
    regs[0xF] = 0x1;
  }
  regs[to] += regs.at(from);
}

void Inst_8XY5(Opcode opcode, RegsT& regs) {
  auto from = third(opcode);
  auto to = second(opcode);
  regs[0xF] = 0;
  if (regs.at(to) > regs.at(from)) {
    regs[0xF] = 0x1;
  }
  regs[to] -= regs.at(from);
}

void Inst_8XY7(Opcode opcode, RegsT& regs) {
  auto from = third(opcode);
  auto to = second(opcode);
  regs[0xF] = 0;
  if (regs.at(from) > regs.at(to)) {
    regs[0xF] = 0x1;
  }
  regs[to] = regs.at(from) - regs.at(to);
}

void Inst_8XY6(Opcode opcode, RegsT& regs) {
  auto reg = second(opcode);
  auto val = regs[reg];
  regs[0xF] = 0x01 & val;
  regs[reg] = val >> 1;
}

void Inst_8XYE(Opcode opcode, RegsT& regs) {
  auto reg = second(opcode);
  auto val = regs[reg];
  regs[0xF] = val >> 7;
  regs[reg] = val << 1;
}

// set index register I to NNN
void Inst_ANNN(Opcode opcode, Memory::Index& i) { i = lastThree(opcode); }

// jump with offset (table lookup)
void Inst_BNNN(Opcode opcode, const RegsT& regs, Memory::Index& pc) {
  auto val = regs[0x0];
  pc = val + lastThree(opcode);
}

// Generate random number
void Inst_CXNN(Opcode opcode, RegsT& regs) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint8_t> distrib(0x00, 0xFF);

  auto reg = second(opcode);
  auto mask = lastTwo(opcode);
  regs[reg] = mask & distrib(gen);
}

// draw sprite
void Inst_DXYN(Opcode opcode, RegsT& regs, const Memory& mem,
               const Memory::Index& i, Display& dis) {
  const auto x = second(opcode);
  const auto y = third(opcode);
  const auto n = fourth(opcode);
  regs[0xF] = 0;
  if (drawSprite(regs.at(y), regs.at(x), readN(mem, i, n), dis)) {
    regs[0xF] = 1;
  }
}

// skip if key is pressed
void Inst_EX9E(Opcode opcode, const KeysT& keys, const RegsT& regs,
               Memory::Index& pc) {
  auto reg = second(opcode);
  if (keys[regs.at(reg)]) {
    pc += OPCODE_SIZE_WORDS;
  }
}

// skip if key is not pressed
void Inst_EXA1(Opcode opcode, const KeysT& keys, const RegsT& regs,
               Memory::Index& pc) {
  auto reg = second(opcode);
  if (!keys[regs.at(reg)]) {
    pc += OPCODE_SIZE_WORDS;
  }
}

// read delay timer
void Inst_FX07(Opcode opcode, const Timer& delay_timer, RegsT& regs) {
  auto reg = second(opcode);
  regs[reg] = delay_timer.get();
}

// set delay timer
void Inst_FX15(Opcode opcode, const RegsT& regs, Timer& delay_timer) {
  auto reg = second(opcode);
  delay_timer.reset(regs[reg]);
}

// set sound timer
void Inst_FX18(Opcode opcode, const RegsT& regs, Timer& sound_timer) {
  auto reg = second(opcode);
  sound_timer.reset(regs[reg]);
}

// Adds to register I
void Inst_FX1E(Opcode opcode, const RegsT& regs, Memory::Index& i) {
  auto reg = second(opcode);
  i += regs[reg];
}

// get key
void Inst_FX0A(Opcode opcode, const KeysT& keys, RegsT& regs,
               Memory::Index& pc) {
  for (KeyT i = 0; i < 16; ++i) {
    if (keys.at(i)) {
      auto reg = second(opcode);
      regs[reg] = i;
      return;
    }
  }

  // if no key pressed just block
  pc -= OPCODE_SIZE_WORDS;
}

// sets I to font character
void Inst_FX29(Opcode opcode, const RegsT& regs, Memory::Index& i) {
  // TODO: what if value in Vx bigger than 15?
  auto reg = second(opcode);
  i = Memory::FONTS_BEGIN + Memory::FONT_SPRITE_WIDTH * regs[reg];
}

// stores decimal in memory at location I
void Inst_FX33(Opcode opcode, const RegsT& regs, const Memory::Index& i,
               Memory& mem) {
  auto value = regs[second(opcode)];
  mem.write(i + 2, value % 10);
  mem.write(i + 1, (value / 10) % 10);
  mem.write(i, (value / 100) % 10);
}

// write memory
void Inst_FX55(Opcode opcode, const RegsT& regs, const Memory::Index& i,
               Memory& mem) {
  for (int r = 0; r < second(opcode) + 1; ++r) {
    mem.write(i + r, regs[r]);
  }
}

// read memory
void Inst_FX65(Opcode opcode, const Memory::Index& i, Memory& mem,
               RegsT& regs) {
  for (int r = 0; r < second(opcode) + 1; ++r) {
    regs[r] = mem.read(i + r);
  }
}
