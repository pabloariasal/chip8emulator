#include <catch2/catch.hpp>

#include "bitmap.h"

TEST_CASE("Bitmaps work as expected", "[bitmap]") {
  // allocate a 4x4 array with the numbers 0-15
  //  0  1  2  3
  //  4  5  6  7
  //  8  9  10 11
  //  12 13 14 15
  auto v = std::vector<int>(16, 0);
  std::iota(v.begin(), v.end(), 0);

  auto buff = PixelBuffer<int>{4, v};

  // TODO: check error cases
  // TODO: test post and pre increment

  SECTION("empty bitmap") {
    auto bm = Bitmap<int>(0, 0, 0, 0, buff);
    (void)bm;
    // TODO: how should iterators behave in this case?
    /* REQUIRE(bm.begin() == bm.end()); */
  }

  SECTION("bitmap iterator works as expected 1/2") {
    auto bm = Bitmap<int>(4, 4, 0, 0, buff);

    auto begin = bm.begin();
    auto end = bm.end();
    REQUIRE(std::distance(begin, end) == 16);

    for (int i = 0; i < 16; ++i) {
      REQUIRE(*(begin++) == i);
    }
  }

  SECTION("bitmap iterator works as expected 2/2") {
    auto bm = Bitmap<int>(2, 2, 1, 1, buff);

    auto begin = bm.begin();
    auto end = bm.end();
    REQUIRE(std::distance(begin, end) == 4);

    for (auto i : {5, 6, 9, 10}) {
      REQUIRE(*(begin++) == i);
    }
  }

  SECTION("bitmaps can modify underlying data") {
    std::fill(v.begin(), v.end(), 0);

    // last column
    auto bm1 = Bitmap<int>(1, 4, 3, 0, buff);
    REQUIRE(std::count(bm1.begin(), bm1.end(), 0) == 4);

    // last row
    auto bm2 = Bitmap<int>(4, 1, 0, 3, buff);
    REQUIRE(std::count(bm2.begin(), bm2.end(), 0) == 4);

    std::fill(bm2.begin(), bm2.end(), 1);
    REQUIRE(std::count(bm2.begin(), bm2.end(), 0) == 0);
    REQUIRE(std::count(bm2.begin(), bm2.end(), 1) == 4);

    REQUIRE(std::count(bm1.begin(), bm1.end(), 0) == 3);
    REQUIRE(std::count(bm1.begin(), bm1.end(), 1) == 1);
  }
}
