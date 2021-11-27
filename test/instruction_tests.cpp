#include <catch2/catch.hpp>
#include <map>

#include "inst.h"
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

TEST_CASE("FX55/FX65 Memory Read Write") {
  auto mem = Memory{};
  auto regs = RegsT{};
  auto i = 5;

  SECTION("Write single word") {
    regs[0] = 4;
    Inst_FX55(0xF055, regs, i, mem);
    auto non_zero_mem_entries = entriesUnequalZero(mem);
    REQUIRE(non_zero_mem_entries.size() == 1);
    REQUIRE(non_zero_mem_entries.at(i) == 4);
  }

  SECTION("Read single word") {
    mem.write(i, 6);
    Inst_FX65(0xF065, i, mem, regs);
    auto non_zero_regs = entriesUnequalZero(regs);
    REQUIRE(non_zero_regs.size() == 1);
    REQUIRE(non_zero_regs.at(0) == 6);
  }

  SECTION("Write multiple words") {
    regs[0] = 1;
    regs[1] = 2;
    regs[2] = 3;
    Inst_FX55(0xF255, regs, i, mem);
    auto non_zero_mem_entries = entriesUnequalZero(mem);
    REQUIRE(non_zero_mem_entries.size() == 3);
    REQUIRE(non_zero_mem_entries.at(i + 0) == 1);
    REQUIRE(non_zero_mem_entries.at(i + 1) == 2);
    REQUIRE(non_zero_mem_entries.at(i + 2) == 3);
  }

  SECTION("Read multiple words") {
    mem.write(i + 0, 1);
    mem.write(i + 1, 2);
    mem.write(i + 2, 3);
    Inst_FX65(0xF265, i, mem, regs);
    auto non_zero_regs = entriesUnequalZero(regs);
    REQUIRE(non_zero_regs.size() == 3);
    REQUIRE(non_zero_regs.at(0) == 1);
    REQUIRE(non_zero_regs.at(1) == 2);
    REQUIRE(non_zero_regs.at(2) == 3);
  }
}

TEST_CASE("6XNN - Registers") {
  auto regs = RegsT{};
  SECTION("Set register to value") {
    Inst_6XNN(0x6F03, regs);
    Inst_6XNN(0x6013, regs);

    auto non_zero_regs = entriesUnequalZero(regs);
    REQUIRE(non_zero_regs.size() == 2);
    REQUIRE(non_zero_regs.at(0xF) == 3);
    REQUIRE(non_zero_regs.at(0x0) == 0x13);
  }
}
