#include <catch2/catch_test_macros.hpp>
#include <sstream>

#include "mem.h"

TEST_CASE("ROM is loaded into memory", "[mem]") {
  std::istringstream stream("abc");

  Memory mem;
  mem.loadROM(stream);

  REQUIRE(mem.at(Memory::ROM_BEGIN + 0) == 'a');
  REQUIRE(mem.at(Memory::ROM_BEGIN + 1) == 'b');
  REQUIRE(mem.at(Memory::ROM_BEGIN + 2) == 'c');
}
