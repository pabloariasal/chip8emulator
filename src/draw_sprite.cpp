#include "draw_sprite.h"

#include <array>

namespace {

bool isPixelSet(int index, uint8_t row) {
  row >>= 7 - index;
  return (row & 0x01u) == 1;
}

bool invertColor(Color& color) {
  if (color == Color::BLACK) {
    color = Color::WHITE;
    return true;
  }
  color = Color::BLACK;
  return false;
}
}  // namespace

bool drawSprite(int row, int col, const std::vector<uint8_t>& sprite,
                PixelBuffer<Color>& display) {
  // wrap coordinates
  row = row % display.height();
  col = col % display.width();

  auto num_sprite_rows = static_cast<int>(sprite.size());
  auto flipped = false;

  for (int sr = 0, x = row; sr < num_sprite_rows && x < display.height();
       sr++, ++x) {
    for (int sc = 0, y = col; sc < 8 && y < display.width(); sc++, ++y) {
      if (isPixelSet(sc, sprite.at(sr))) {
        if (invertColor(display.get(x, y))) {
          flipped = true;
        }
      }
    }
  }

  return flipped;
}
