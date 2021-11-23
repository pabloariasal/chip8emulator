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
    drawSprite(0, 0, {0, {}}, buf);
    REQUIRE(indicesWithColor(buf, Color::BLACK).empty());
  }

  SECTION("all-white sprite has no effect") {
    buf.data().front() = Color::BLACK;
    REQUIRE(indicesWithColor(buf, Color::BLACK).size() == 1);

    auto sprite = PixelBuffer<Color>::init(2, 2, Color::WHITE);
    drawSprite(0, 0, sprite, buf);
    REQUIRE(indicesWithColor(buf, Color::BLACK).size() == 1);
  }

  SECTION("draw all-black sprite on screen") {
    auto sprite = PixelBuffer<Color>::init(2, 2, Color::BLACK);
    drawSprite(0, 1, sprite, buf);

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
    drawSprite(0, 0, sprite, buf);

    REQUIRE(indicesWithColor(buf, Color::BLACK).empty());
  }

  SECTION("draw middle row and col") {
    auto sprite_row = PixelBuffer<Color>::init(3, 1, Color::BLACK);
    auto sprite_col = PixelBuffer<Color>::init(1, 3, Color::BLACK);
    drawSprite(1, 0, sprite_row, buf);
    drawSprite(0, 1, sprite_col, buf);

    const auto expected =
        indicesFromPairs({{0, 1}, {1, 0}, {1, 2}, {2, 1}}, buf);
    const auto actual = indicesWithColor(buf, Color::BLACK);
    REQUIRE(expected == actual);
  }

  SECTION("sprite with coordinate overflow") {
    // TODO:
  }

  SECTION("sprite with draw overflow") {
    // TODO:
  }
}