#include "draw_sprite.h"

#include <array>

namespace {

std::array<bool, 8> toArray(uint8_t row) {
  std::array<bool, 8> sprite{};
  for (int i = 0; i < 8; ++i) {
    if ((row & 0x01u) == 1) {
      sprite[7 - i] = true;
    }
    row >>= 1;
  }
  /* std::reverse(sprite.begin(), sprite.end()); */
  return sprite;
}

}  // namespace

bool drawSprite(int row, int col, const std::vector<uint8_t>& sprite,
                PixelBuffer<Color>& display) {
  auto flipped = false;

  auto y = row % display.height();
  for (const auto& sprite_row : sprite) {
    auto x = col % display.width();
    auto sprite_row_array = toArray(sprite_row);
    for (auto sprite_pixel : sprite_row_array) {
      if (sprite_pixel) {
        if (display.get(y, x) == Color::BLACK) {
          display.get(y, x) = Color::WHITE;
          flipped = true;
        } else {
          display.get(y, x) = Color::BLACK;
        }
      }
      if (x >= display.width()) {
        break;
      }
      ++x;
    }
    if (y >= display.height()) {
      break;
    }
    ++y;
  }

  return flipped;
}
