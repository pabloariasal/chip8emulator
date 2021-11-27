#include <catch2/catch.hpp>

#include "inst.h"
#include "state.h"

namespace {
Opcode op(std::string s) {
  assert(s.size() == 4);

  Opcode opcode{};
  for (int i = 0; i < 4; ++i) {
    opcode = opcode << i;
    opcode |= s[i];
  }

  return opcode;
}
}  // namespace

TEST_CASE("FX55/FX65", "[instruction]") {
  auto mem = Memory{};
  auto regs = RegsT{};
  auto i = 5;

  SECTION("Write single word") {
    regs[0] = 4;
    Inst_FX55(op("F055"), regs, i, mem);
    REQUIRE(mem.read(i) == 4);
  }

  SECTION("Read single word") {
    mem.write(i, 6);
    Inst_FX65(op("F065"), i, mem, regs);
    REQUIRE(regs[0] == 6);
  }

  SECTION("Write multiple words") {
    regs[0] = 1;
    regs[1] = 2;
    regs[2] = 3;
    Inst_FX55(op("F055"), regs, i, mem);
    REQUIRE(mem.read(i + 0) == 1);
    REQUIRE(mem.read(i + 1) == 2);
    REQUIRE(mem.read(i + 2) == 3);
  }

  SECTION("Read multiple words") {
    mem.write(i + 0, 1);
    mem.write(i + 1, 2);
    mem.write(i + 2, 3);
    Inst_FX65(op("F065"), i, mem, regs);
    REQUIRE(regs[0] == 1);
    REQUIRE(regs[1] == 2);
    REQUIRE(regs[2] == 3);
  }
}
