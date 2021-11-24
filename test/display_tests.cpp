#include <catch2/catch.hpp>
#include <unordered_set>

#include "display.h"

namespace {

struct Pair {
  int x;
  int y;
};

std::unordered_set<size_t> indicesFromPairs(std::initializer_list<Pair> pairs,
                                            const PixelBuffer<Color>& buf) {
  std::unordered_set<size_t> res;
  res.reserve(pairs.size());
  std::transform(pairs.begin(), pairs.end(), std::inserter(res, res.end()),
                 [&buf](const auto& p) { return p.x * buf.width() + p.y; });
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

TEST_CASE("sprite rendering", "[display]") {
  //  0  1  2
  //  3  4  5
  //  6  7  8
  auto buf = PixelBuffer<Color>::init(3, 3, Color::WHITE);

  SECTION("0x0 sprite") {
    REQUIRE(drawSprite(0, 0, {0, {}}, buf) == false);
    REQUIRE(indicesWithColor(buf, Color::BLACK).empty());

    auto sp1 = PixelBuffer<Color>::init(0, 5, Color::BLACK);
    REQUIRE(drawSprite(0, 0, sp1, buf) == false);
    REQUIRE(indicesWithColor(buf, Color::BLACK).empty());

    auto sp2 = PixelBuffer<Color>::init(5, 0, Color::BLACK);
    REQUIRE(drawSprite(0, 0, sp2, buf) == false);
    REQUIRE(indicesWithColor(buf, Color::BLACK).empty());
  }

  SECTION("0x0 bitmap") {
    auto empty = PixelBuffer<Color>::init(0, 0, Color::WHITE);
    auto sprite = PixelBuffer<Color>::init(4, 4, Color::BLACK);
    REQUIRE(drawSprite(0, 0, sprite, empty) == false);
    REQUIRE(indicesWithColor(buf, Color::BLACK).empty());
  }

  SECTION("all-white sprite has no effect") {
    buf.data().front() = Color::BLACK;
    REQUIRE(indicesWithColor(buf, Color::BLACK).size() == 1);

    auto sprite = PixelBuffer<Color>::init(2, 2, Color::WHITE);
    REQUIRE(drawSprite(0, 0, sprite, buf) == false);
    REQUIRE(indicesWithColor(buf, Color::BLACK).size() == 1);
  }

  SECTION("draw all-black sprite on screen") {
    auto sprite = PixelBuffer<Color>::init(2, 2, Color::BLACK);
    REQUIRE(drawSprite(0, 1, sprite, buf) == true);

    const auto expected =
        indicesFromPairs({{0, 1}, {0, 2}, {1, 1}, {1, 2}}, buf);
    const auto actual = indicesWithColor(buf, Color::BLACK);
    REQUIRE(expected == actual);
  }

  SECTION("flip two pixels") {
    buf.data().front() = Color::BLACK;
    buf.data().back() = Color::BLACK;
    REQUIRE(indicesWithColor(buf, Color::BLACK).size() == 2);

    auto sprite = PixelBuffer<Color>::init(3, 3, Color::WHITE);
    sprite.data().front() = Color::BLACK;
    sprite.data().back() = Color::BLACK;
    REQUIRE(drawSprite(0, 0, sprite, buf) == true);

    REQUIRE(indicesWithColor(buf, Color::BLACK).empty());
  }

  SECTION("draw middle row and col") {
    auto sprite_row = PixelBuffer<Color>::init(3, 1, Color::BLACK);
    auto sprite_col = PixelBuffer<Color>::init(1, 3, Color::BLACK);
    REQUIRE(drawSprite(1, 0, sprite_row, buf) == true);
    REQUIRE(drawSprite(0, 1, sprite_col, buf) == true);

    const auto expected =
        indicesFromPairs({{0, 1}, {1, 0}, {1, 2}, {2, 1}}, buf);
    const auto actual = indicesWithColor(buf, Color::BLACK);
    REQUIRE(expected == actual);
  }

  SECTION("sprite with coordinate overflow") {
    // coordinates are allowed to exceed the boundaries of the screen
    // in this case they show wrap around.

    auto sprite = PixelBuffer<Color>::init(1, 1, Color::BLACK);
    // row = 5, col = 3 correspond to row = 2, col = 0 in our 3x3 screen
    REQUIRE(drawSprite(5, 3, sprite, buf) == true);

    const auto expected = indicesFromPairs({{2, 0}}, buf);
    const auto actual = indicesWithColor(buf, Color::BLACK);
    REQUIRE(expected == actual);
  }

  SECTION("sprite with draw overflow") {
    auto sprite = PixelBuffer<Color>::init(100, 100, Color::BLACK);
    REQUIRE(drawSprite(0, 0, sprite, buf) == true);
    REQUIRE(indicesWithColor(buf, Color::BLACK).size() == buf.data().size());

    REQUIRE(drawSprite(4, 4, sprite, buf) == true);
    REQUIRE(indicesWithColor(buf, Color::BLACK).size() == 5);
  }
}
