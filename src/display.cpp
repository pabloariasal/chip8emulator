#include "display.h"

#include <algorithm>
#include <functional>

namespace {
Color xor_colors(const Color& c1, const Color& c2) {
  if (c1 != c2) {
    return Color::BLACK;
  } else {
    return Color::WHITE;
  }
}
}  // namespace

void drawSprite(const Sprite& sprite, Bitmap& bitmap) {
  const auto x = sprite.width != 0 ? sprite.x % bitmap.width : 0;
  const auto y = sprite.height != 0 ? sprite.y % bitmap.height : 0;

  for (int row_offset = 0; row_offset < sprite.height; ++row_offset) {
    const auto begin_index = bitmap.index(x + row_offset, y);
    const auto begin = bitmap.data.begin() + begin_index;
    const auto end = begin + sprite.width;
    std::transform(begin, end, begin,
                   std::bind(xor_colors, Color::BLACK, std::placeholders::_1));
  }
}
