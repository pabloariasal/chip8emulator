#include "display.h"

#include <algorithm>
#include <functional>

#include "bitmap.h"
#include "sprite.h"

namespace {
[[maybe_unused]] Color xor_colors(const Color& c1, const Color& c2) {
  if (c1 != c2) {
    return Color::BLACK;
  } else {
    return Color::WHITE;
  }
}
}  // namespace

bool drawSprite(int row, int col, const PixelBuffer<Color>& sprite,
                PixelBuffer<Color>& screen) {
  /* const auto x = sprite.data.width() != 0 ? sprite.x % bitmap.width() : 0; */
  /* const auto y = sprite.data.height() != 0 ? sprite.y % bitmap.height() : 0;
   */

  return false;
}
