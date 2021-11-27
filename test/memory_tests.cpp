#include <catch2/catch.hpp>
#include <sstream>

#include "mem.h"

TEST_CASE("Memory Tests") {
  Memory mem;

  SECTION("ROM loading") {
    std::istringstream stream("abc");

    mem.loadROM(stream);

    REQUIRE(mem.read(Memory::ROM_BEGIN + 0) == 'a');
    REQUIRE(mem.read(Memory::ROM_BEGIN + 1) == 'b');
    REQUIRE(mem.read(Memory::ROM_BEGIN + 2) == 'c');
  }
  SECTION("Read/Write") {
    mem.write(0, 1);
    mem.write(1, 2);
    mem.write(2, 3);
    REQUIRE(mem.read(0) == 1);
    REQUIRE(mem.read(1) == 2);
    REQUIRE(mem.read(2) == 3);
  }

  SECTION("readN") {
    mem.write(10, 1);
    mem.write(11, 2);
    mem.write(12, 3);
    REQUIRE(readN(mem, 10, 4) == std::vector<Memory::Word>{1, 2, 3, 0});
  }
}
