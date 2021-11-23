#include <catch2/catch.hpp>
#include <unordered_set>

#include "bitmap.h"
#include "display.h"
#include "sprite.h"

namespace {

struct Pair {
  int x;
  int y;
};

/* std::unordered_set<size_t> indicesFromPairs(std::initializer_list<Pair> pairs, */
/*                                             const Bitmap& bm) { */
/*   std::unordered_set<size_t> res; */
/*   res.reserve(pairs.size()); */
/*   std::transform(pairs.begin(), pairs.end(), std::inserter(res, res.end()), */
/*                  [&bm](const auto& p) { return bm.index(p.x, p.y); }); */
/*   return res; */
/* } */

std::unordered_set<size_t> indicesWithColor(const Bitmap& bm, Color color) {
  std::unordered_set<size_t> res;
  res.reserve(bm.data.size());

  for (size_t i = 0; i < bm.data.size(); ++i) {
    if (bm.data[i] == color) {
      res.insert(i);
    }
  }
  return res;
}
}  // namespace

TEST_CASE("bitmap initialization", "[display]") {
  SECTION("empty bitmaps can be created") {
    const auto empty = Bitmap::initialize(0, 0, Color::BLACK);

    REQUIRE(empty.width == 0);
    REQUIRE(empty.height == 0);
    REQUIRE(empty.data.empty());
  }
  SECTION("bitmaps are correctly initialized") {
    constexpr auto width = 64;
    constexpr auto height = 32;
    const auto bitmap = Bitmap::initialize(width, height, Color::BLACK);

    REQUIRE(bitmap.width == width);
    REQUIRE(bitmap.height == height);
    REQUIRE(bitmap.data.size() == width * height);
    REQUIRE(bitmap.data.front() == Color::BLACK);
    REQUIRE(bitmap.data.back() == Color::BLACK);
  }
}

TEST_CASE("sprite rendering", "[display]") {
  auto bm = Bitmap::initialize(3, 3);
  SECTION("0x0 sprite") {
    drawSprite(Sprite{0, 0, 0, {}}, bm);
    REQUIRE(indicesWithColor(bm, Color::BLACK).empty());
  }

  /* SECTION("2x1 sprite") { */
  /*   drawSprite({1, 1, 2, 1}, bm); */

  /*   const auto expected = indicesFromPairs({{1, 1}, {1, 2}}, bm); */
  /*   const auto actual = indicesWithColor(bm, Color::BLACK); */
  /*   REQUIRE(expected == actual); */
  /* } */

  /* SECTION("sprite with hole") { */
  /*   // paint the whole bitmap black */
  /*   drawSprite({0, 0, 3, 3}, bm); */

  /*   REQUIRE(indicesWithColor(bm, Color::WHITE).empty()); */

  /*   // now paint the middle pixel black, should turn white */
  /*   drawSprite({1, 1, 1, 1}, bm); */

  /*   const auto expected = indicesFromPairs({{1, 1}}, bm); */
  /*   const auto actual = indicesWithColor(bm, Color::WHITE); */
  /*   REQUIRE(expected == actual); */
  /* } */
  /* SECTION("sprite with coordinate overflow") { */
  /*   // coordinates outside the bitmap should wrap */

  /*   // x = 7, y = 8 should be the same as x = 1, y = 2 */
  /*   drawSprite({7, 8, 1, 1}, bm); */

  /*   const auto expected = indicesFromPairs({{1, 2}}, bm); */
  /*   const auto actual = indicesWithColor(bm, Color::BLACK); */
  /*   REQUIRE(expected == actual); */
  /* } */
  /* SECTION("sprite with draw overflow") {} */
}
