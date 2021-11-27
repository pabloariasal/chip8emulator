#include "display.h"

#include <algorithm>

#include "bitmap.h"

namespace {
[[nodiscard]] Color xor_colors(const Color& sprite_pixel,
                               const Color& screen_pixel) {
  if (sprite_pixel == Color::BLACK) {
    if (screen_pixel == Color::BLACK) {
      return Color::WHITE;
    } else {
      return Color::BLACK;
    }
  }
  return screen_pixel;
}
}  // namespace

bool drawSprite(int row, int col, const PixelBuffer<Color>& sprite,
                PixelBuffer<Color>& screen) {
  if (screen.width() == 0 || screen.height() == 0 || sprite.width() == 0 ||
      sprite.height() == 0) {
    return false;
  }

  // normalize screen coordinates
  const auto x = col % screen.width();
  const auto y = row % screen.height();

  // clip sprite
  const auto w =
      x + sprite.width() > screen.width() ? screen.width() - x : sprite.width();
  const auto h = y + sprite.height() > screen.height() ? screen.height() - y
                                                       : sprite.height();

  auto screen_view = Bitmap<Color>(w, h, x, y, screen);
  auto sprite_view =
      Bitmap<Color>(w, h, 0, 0, const_cast<PixelBuffer<Color>&>(sprite));

  auto flipped = false;

  std::transform(
      sprite_view.begin(), sprite_view.end(), screen_view.begin(),
      screen_view.begin(),
      [&flipped](const auto& sprite_pixel, const auto& screen_pixel) {
        auto c = xor_colors(sprite_pixel, screen_pixel);
        if (!flipped && c != screen_pixel) {
          flipped = true;
        }
        return c;
      });

  return flipped;
}

std::vector<Color> toColorVec(std::vector<uint8_t> sprite_pixels) {
  std::vector<Color> res;
  res.reserve(8 * sprite_pixels.size());

  for (auto r : sprite_pixels) {
    for (int i = 0; i < 8; ++i) {
      res.push_back((r & 0x01) == 0 ? Color::BLACK : Color::WHITE);
      r >>= 1;
    }
  }

  return res;
}
