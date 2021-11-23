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
  const auto w = sprite.width();
  const auto h = sprite.height();

  const auto x =
      col;  // sprite.data.width() != 0 ? sprite.x % bitmap.width() : 0;
  const auto y =
      row;  // sprite.data.height() != 0 ? sprite.y % bitmap.height() : 0;
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

  return false;
}
