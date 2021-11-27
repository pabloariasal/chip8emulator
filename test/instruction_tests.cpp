#include <catch2/catch.hpp>
#include <map>

#include "process_instruction.h"
#include "state.h"

namespace {

std::map<Memory::Index, Memory::Word> entriesUnequalZero(const Memory& mem) {
  std::map<Memory::Index, Memory::Word> res;
  for (int i = 0; i < Memory::MEM_SIZE; ++i) {
    if (auto m = mem.read(i); m != 0) {
      res[i] = m;
    }
  }
  return res;
}

std::map<uint8_t, RegT> entriesUnequalZero(const RegsT& regs) {
  std::map<uint8_t, RegT> res;
  for (size_t i = 0; i < regs.size(); ++i) {
    if (auto v = regs.at(i); v != 0) {
      res[i] = v;
    }
  }
  return res;
}

}  // namespace

TEST_CASE("Next Opcode Tests") {
  auto s = State{};
  SECTION("Next opcode") {
    s.mem.write(Memory::ROM_BEGIN, 0x12);
    s.mem.write(Memory::ROM_BEGIN + 1, 0x34);

    s.mem.write(Memory::ROM_BEGIN + 2, 0x56);
    s.mem.write(Memory::ROM_BEGIN + 3, 0x78);

    REQUIRE(s.pc == Memory::ROM_BEGIN);
    REQUIRE(nextOpcode(s) == 0x1234);
    REQUIRE(s.pc == Memory::ROM_BEGIN + 2);

    REQUIRE(nextOpcode(s) == 0x5678);
    REQUIRE(s.pc == Memory::ROM_BEGIN + 4);
  }
}

TEST_CASE("FX55/FX65 Memory Read Write") {
  auto s = State{};

  SECTION("Write single word") {
    s.regs[0] = 4;
    processInstruction(0xF055, s);
    auto non_zero_mem_entries = entriesUnequalZero(s.mem);
    REQUIRE(non_zero_mem_entries.size() == 1);
    REQUIRE(non_zero_mem_entries.at(s.i) == 4);
  }

  SECTION("Read single word") {
    s.mem.write(s.i, 6);
    processInstruction(0xF065, s);
    auto non_zero_regs = entriesUnequalZero(s.regs);
    REQUIRE(non_zero_regs.size() == 1);
    REQUIRE(non_zero_regs.at(0) == 6);
  }

  SECTION("Write multiple words") {
    s.regs[0] = 1;
    s.regs[1] = 2;
    s.regs[2] = 3;
    processInstruction(0xF255, s);
    auto non_zero_mem_entries = entriesUnequalZero(s.mem);
    REQUIRE(non_zero_mem_entries.size() == 3);
    REQUIRE(non_zero_mem_entries.at(s.i + 0) == 1);
    REQUIRE(non_zero_mem_entries.at(s.i + 1) == 2);
    REQUIRE(non_zero_mem_entries.at(s.i + 2) == 3);
  }

  SECTION("Read multiple words") {
    s.mem.write(s.i + 0, 1);
    s.mem.write(s.i + 1, 2);
    s.mem.write(s.i + 2, 3);
    processInstruction(0xF265, s);
    auto non_zero_regs = entriesUnequalZero(s.regs);
    REQUIRE(non_zero_regs.size() == 3);
    REQUIRE(non_zero_regs.at(0) == 1);
    REQUIRE(non_zero_regs.at(1) == 2);
    REQUIRE(non_zero_regs.at(2) == 3);
  }
}

TEST_CASE("6XNN/7XNN/ANNN - Registers") {
  auto s = State{};
  SECTION("Set register to value") {
    processInstruction(0x6F03, s);
    processInstruction(0x6013, s);

    auto non_zero_regs = entriesUnequalZero(s.regs);
    REQUIRE(non_zero_regs.size() == 2);
    REQUIRE(non_zero_regs.at(0xF) == 3);
    REQUIRE(non_zero_regs.at(0x0) == 0x13);
  }
  SECTION("Add value to register") {
    processInstruction(0x6C03, s);
    processInstruction(0x7C03, s);

    auto non_zero_regs = entriesUnequalZero(s.regs);
    REQUIRE(non_zero_regs.size() == 1);
    REQUIRE(non_zero_regs.at(0xC) == 6);
  }
  SECTION("Set Index Register") {
    processInstruction(0xA003, s);
    REQUIRE(s.i == 3);

    processInstruction(0xAFFF, s);
    REQUIRE(s.i == 0xFFF);
  }
}
