#include <catch2/catch.hpp>

#include "color.h"
#include "pixel_buffer.h"

// TODO: complete this
TEST_CASE("PixelBuffer Tests") {
  auto buf = PixelBuffer<Color>(3, 3, Color::WHITE);
  SECTION("set all pixels") {
    REQUIRE(std::all_of(buf.cbegin(), buf.cend(),
                        [](const auto& e) { return e == Color::WHITE; }));
    buf.setAll(Color::BLACK);
    REQUIRE(std::all_of(buf.cbegin(), buf.cend(),
                        [](const auto& e) { return e == Color::BLACK; }));
  }
}
