// TODO: split this class
#include <catch2/catch.hpp>
#include <map>
#include <unordered_set>

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
    REQUIRE(s.pc == Memory::ROM_BEGIN + OPCODE_SIZE_WORDS * 1);

    REQUIRE(nextOpcode(s) == 0x5678);
    REQUIRE(s.pc == Memory::ROM_BEGIN + OPCODE_SIZE_WORDS * 2);
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

namespace {

struct Pair {
  int row;
  int col;
};

std::unordered_set<size_t> indicesFromPairs(std::initializer_list<Pair> pairs,
                                            const PixelBuffer<Color>& buf) {
  std::unordered_set<size_t> res;
  res.reserve(pairs.size());
  std::transform(pairs.begin(), pairs.end(), std::inserter(res, res.end()),
                 [&buf](const auto& p) { return p.row * buf.width() + p.col; });
  return res;
}

std::unordered_set<size_t> indicesWithColor(const PixelBuffer<Color>& buf,
                                            Color color) {
  std::unordered_set<size_t> res;
  res.reserve(buf.data().size());

  for (size_t i = 0; i < buf.data().size(); ++i) {
    if (buf.data()[i] == color) {
      res.insert(i);
    }
  }
  return res;
}
}  // namespace

TEST_CASE("DXYN") {
  auto s = State{};
  s.i = 5;

  s.mem.write(s.i, 0x80u);
  s.mem.write(s.i + 1, 0x01u);

  s.regs[1] = 1;  // horizontal
  s.regs[2] = 2;  // vertical

  SECTION("draw zero rows") {
    processInstruction(0xD120, s);
    REQUIRE(indicesWithColor(s.display, Color::BLACK).empty());
    REQUIRE(s.regs[0xF] == 0);
  }

  SECTION("draw one row") {
    processInstruction(0xD121, s);
    const auto expected = indicesFromPairs({{2, 1}}, s.display);
    const auto actual = indicesWithColor(s.display, Color::BLACK);
    REQUIRE(expected == actual);
    REQUIRE(s.regs[0xF] == 0);
  }

  SECTION("draw two rows") {
    processInstruction(0xD122, s);
    const auto expected = indicesFromPairs({{2, 1}, {3, 8}}, s.display);
    const auto actual = indicesWithColor(s.display, Color::BLACK);
    REQUIRE(expected == actual);
    REQUIRE(s.regs[0xF] == 0);
  }

  SECTION("drawing the same sprite two times clears the screen") {
    processInstruction(0xD121, s);
    REQUIRE(s.regs[0xF] == 0);
    processInstruction(0xD121, s);
    REQUIRE(s.regs[0xF] == 1);
    REQUIRE(indicesWithColor(s.display, Color::BLACK).empty());
  }

  SECTION("coordinate oveflow") {
    s.regs[1] = Display::SCREEN_WIDTH + 1;   // corresponds to second column
    s.regs[2] = Display::SCREEN_HEIGHT + 2;  // corresponds to third row
    processInstruction(0xD121, s);
    const auto expected = indicesFromPairs({{2, 1}}, s.display);
    const auto actual = indicesWithColor(s.display, Color::BLACK);
    REQUIRE(expected == actual);
    REQUIRE(s.regs[0xF] == 0);
  }
  SECTION("coordinate oveflow") {
    s.regs[1] = Display::SCREEN_WIDTH - 1;   // corresponds to second column
    s.regs[2] = Display::SCREEN_HEIGHT - 1;  // corresponds to third row
    processInstruction(0xD122, s);
    const auto expected = indicesFromPairs(
        {{Display::SCREEN_HEIGHT - 1, Display::SCREEN_WIDTH - 1}}, s.display);
    const auto actual = indicesWithColor(s.display, Color::BLACK);
    REQUIRE(expected == actual);
    REQUIRE(s.regs[0xF] == 0);
  }
}

TEST_CASE("Skip Control Flow - 3XNN/4XNN/5XY0/9XY0") {
  auto s = State{};
  SECTION("Jump if value in vx is equal") {
    auto pc = s.pc;
    s.regs[0x8] = 0x8;
    processInstruction(0x3813, s);
    REQUIRE(s.pc == pc);

    s.regs[0xA] = 0xAA;
    processInstruction(0x3AAA, s);
    REQUIRE(s.pc == pc + OPCODE_SIZE_WORDS);
  }
  SECTION("Jump if value in vx is not equal") {
    auto pc = s.pc;
    s.regs[0xA] = 0xAA;
    processInstruction(0x4AAA, s);
    REQUIRE(s.pc == pc);

    s.regs[0x8] = 8;
    processInstruction(0x4813, s);
    REQUIRE(s.pc == pc + OPCODE_SIZE_WORDS);
  }
  SECTION("Jump if values in regs equals") {
    auto pc = s.pc;
    s.regs[0xA] = 0xAA;
    s.regs[0xB] = 0x5;
    processInstruction(0x5AB0, s);
    REQUIRE(s.pc == pc);

    s.regs[0xB] = 0xAA;
    processInstruction(0x5AB3, s);
    REQUIRE(s.pc == pc + OPCODE_SIZE_WORDS);
  }
  SECTION("Jump if values in regs not equals") {
    auto pc = s.pc;
    s.regs[0xA] = 0xAA;
    s.regs[0xB] = 0xAA;
    processInstruction(0x9AB0, s);
    REQUIRE(s.pc == pc);

    s.regs[0xB] = 0x5;
    processInstruction(0x9AB0, s);
    REQUIRE(s.pc == pc + OPCODE_SIZE_WORDS);
  }
}

TEST_CASE("00EE/2NNN Subroutines") {
  auto s = State{};
  s.mem.write(0x444, 0x12);
  s.pc = 0x111;
  SECTION("Call subroutine at memory location") {
    processInstruction(0x2444, s);
    REQUIRE(s.pc == 0x444);
    REQUIRE(s.stack.size() == 1);
    REQUIRE(s.stack.top() == 0x111);
  }
  SECTION("Returning from a subroutine") {
    // first call a subroutine
    processInstruction(0x2444, s);
    REQUIRE(s.pc == 0x444);

    // now return from it -> should restore PC
    processInstruction(0x00EE, s);
    REQUIRE(s.stack.empty());
    REQUIRE(s.pc == 0x111);
  }
}

TEST_CASE("Math/Arithmetic Intructions") {
  auto s = State{};
  SECTION("8YX0 - Set the value of register") {
    s.regs[0x6] = 0x7;
    processInstruction(0x8560, s);
    auto non_zero_regs = entriesUnequalZero(s.regs);
    REQUIRE(non_zero_regs.size() == 2);
    REQUIRE(non_zero_regs.at(5) == 7);
  }
  SECTION("8XY1 - Binary OR") {
    s.regs[0xA] = 0x1;
    s.regs[0xB] = 0x2;
    processInstruction(0x8BA1, s);
    auto non_zero_regs = entriesUnequalZero(s.regs);
    REQUIRE(non_zero_regs.size() == 2);
    REQUIRE(non_zero_regs.at(0xB) == 0x3);
    REQUIRE(non_zero_regs.at(0xA) == 0x1);
  }
  SECTION("8XY1 - Binary OR") {
    s.regs[0xA] = 0x1;
    s.regs[0xB] = 0x3;
    processInstruction(0x8BA2, s);
    auto non_zero_regs = entriesUnequalZero(s.regs);
    REQUIRE(non_zero_regs.size() == 2);
    REQUIRE(non_zero_regs.at(0xB) == 0x1);
    REQUIRE(non_zero_regs.at(0xA) == 0x1);
  }
  SECTION("8XY1 - Binary XOR") {
    s.regs[0xA] = 0x1;
    s.regs[0xB] = 0x3;
    processInstruction(0x8BA3, s);
    auto non_zero_regs = entriesUnequalZero(s.regs);
    REQUIRE(non_zero_regs.size() == 2);
    REQUIRE(non_zero_regs.at(0xB) == 0x2);
    REQUIRE(non_zero_regs.at(0xA) == 0x1);
  }
  SECTION("8YX4 - Addition") {
    s.regs[0xA] = 0x1;
    s.regs[0xB] = 0x3;
    processInstruction(0x8BA4, s);
    auto non_zero_regs = entriesUnequalZero(s.regs);
    REQUIRE(non_zero_regs.size() == 2);
    REQUIRE(non_zero_regs.at(0xB) == 0x4);
    REQUIRE(non_zero_regs.at(0xA) == 0x1);

    s.regs[0xC] = 0xFF;

    processInstruction(0x8CB4, s);
    non_zero_regs = entriesUnequalZero(s.regs);
    REQUIRE(non_zero_regs.size() == 4);
    REQUIRE(non_zero_regs.at(0xB) == 0x4);
    REQUIRE(non_zero_regs.at(0xA) == 0x1);
    REQUIRE(non_zero_regs.at(0xC) == 0x3);
    REQUIRE(non_zero_regs.at(0xF) == 0x1);
  }
  SECTION("8YX5 - Substraction") {
    s.regs[0xA] = 0x3;
    s.regs[0xB] = 0x1;
    processInstruction(0x8AB5, s);
    auto non_zero_regs = entriesUnequalZero(s.regs);
    REQUIRE(non_zero_regs.size() == 3);
    REQUIRE(non_zero_regs.at(0xB) == 0x1);
    REQUIRE(non_zero_regs.at(0xA) == 0x2);
    REQUIRE(non_zero_regs.at(0xF) == 0x1);

    processInstruction(0x8BA5, s);
    non_zero_regs = entriesUnequalZero(s.regs);
    REQUIRE(non_zero_regs.size() == 2);
    REQUIRE(non_zero_regs.at(0xB) == 0xFF);  // underflow
    REQUIRE(non_zero_regs.at(0xA) == 0x2);
  }
  SECTION("8XY6 - Shift to the right") {
    s.regs[0x5] = 0x8;  // 00001000
    processInstruction(0x8506, s);
    REQUIRE(s.regs[0x5] == 0x4);
    REQUIRE(s.regs[0xF] == 0x0);

    s.regs[0x4] = 0x9;  // 00001001
    processInstruction(0x8406, s);
    REQUIRE(s.regs[0x4] == 0x4);
    REQUIRE(s.regs[0xF] == 0x1);
  }
  SECTION("8XYE - Shift to the left") {
    s.regs[0x5] = 0x8;  // 00001000
    processInstruction(0x850E, s);
    REQUIRE(s.regs[0x5] == 0x10);
    REQUIRE(s.regs[0xF] == 0x0);

    s.regs[0x4] = 0x88;  // 10001000
    processInstruction(0x840E, s);
    REQUIRE(s.regs[0x4] == 0x10);
    REQUIRE(s.regs[0xF] == 0x1);
  }
}

TEST_CASE("FX0A - Key Input") {
  auto s = State{};
  SECTION("Instruction blocks until a key is pressed") {
    auto old_pc = s.pc;
    processInstruction(0xF40A, s);
    processInstruction(0xF40A, s);
    processInstruction(0xF40A, s);
    auto non_zero_regs = entriesUnequalZero(s.regs);
    REQUIRE(non_zero_regs.empty());
    REQUIRE(old_pc - 3 * OPCODE_SIZE_WORDS == s.pc);
  }
  SECTION("Pressed key is stored in register") {
    auto old_pc = s.pc;
    s.key = 0x6;
    processInstruction(0xF40A, s);
    s.key = 0x9;
    processInstruction(0xF70A, s);

    auto non_zero_regs = entriesUnequalZero(s.regs);
    REQUIRE(non_zero_regs.size() == 2);
    REQUIRE(non_zero_regs.at(0x4) == 0x6);
    REQUIRE(non_zero_regs.at(0x7) == 0x9);
    REQUIRE(old_pc == s.pc);
  }
  SECTION("EX9E - Skip if key pressed") {
    auto old_pc = s.pc;

    s.regs[0x6] = 0xF;
    processInstruction(0xE69E, s);
    REQUIRE(s.pc == old_pc);

    s.key = 0xF;
    processInstruction(0xE69E, s);
    REQUIRE(s.pc == old_pc + OPCODE_SIZE_WORDS);
  }
  SECTION("EXA1 - Skip if key not pressed") {
    auto old_pc = s.pc;

    s.regs[0x6] = 0xF;
    processInstruction(0xE6A1, s);
    REQUIRE(s.pc == old_pc + OPCODE_SIZE_WORDS);

    s.key = 0xF;
    processInstruction(0xE6A1, s);
    REQUIRE(s.pc == old_pc + OPCODE_SIZE_WORDS);
  }
}

TEST_CASE("FX29 - Font character") {
  auto s = State{};
  s.mem.loadFonts();
  SECTION("FX29 - Set i to the address of character 1") {
    s.regs[0xC] = 0x1;
    processInstruction(0xFC29, s);
    auto character_zero_sprite = readN(s.mem, s.i, Memory::FONT_SPRITE_WIDTH);
    REQUIRE(character_zero_sprite ==
            std::vector<Memory::Word>{0x20, 0x60, 0x20, 0x20, 0x70});
  }
  SECTION("FX29 - Set i to the address of character A") {
    s.regs[0xA] = 0xA;
    processInstruction(0xFA29, s);
    auto character_A_sprite = readN(s.mem, s.i, Memory::FONT_SPRITE_WIDTH);
    REQUIRE(character_A_sprite ==
            std::vector<Memory::Word>{0xF0, 0x90, 0xF0, 0x90, 0x90});
  }
}

TEST_CASE("FX33 - Decimal conversion") {
  auto s = State{};
  SECTION("FX33 - Store decimal 156 digits in memory") {
    s.i = 0x12;
    s.regs[0x8] = 0x9C;
    processInstruction(0xF833, s);
    REQUIRE(readN(s.mem, s.i, 3) == std::vector<Memory::Word>{1, 5, 6});
  }
  SECTION("FX33 - Store decimal 255 digits in memory") {
    s.i = 0x12;
    s.regs[0x8] = 0xFF;
    processInstruction(0xF833, s);
    REQUIRE(readN(s.mem, s.i, 3) == std::vector<Memory::Word>{2, 5, 5});
  }
}
