#include <catch2/catch.hpp>

#include "opcode.h"

TEST_CASE("Opcode Tests") {
  SECTION("first") {
    REQUIRE(first(0x1234) == 1);
    REQUIRE(first(0x7234) == 7);
  }
  SECTION("second") {
    REQUIRE(second(0x1234) == 2);
    REQUIRE(second(0x7890) == 8);
    REQUIRE(second(0x7F90) == 15);
    REQUIRE(second(0x7090) == 0);
  }

  SECTION("third") {
    REQUIRE(third(0x1234) == 3);
    REQUIRE(third(0x7890) == 9);
  }

  SECTION("fourth") {
    REQUIRE(fourth(0x1234) == 4);
    REQUIRE(fourth(0x7890) == 0);
  }
  SECTION("lastThree") {
    REQUIRE(lastThree(0x1234) == 0x234);
    REQUIRE(lastThree(0x0005) == 5);
  }
  SECTION("lastTwo") {
    REQUIRE(lastTwo(0x1234) == 0x34);
    REQUIRE(lastTwo(0x0005) == 5);
  }
}
