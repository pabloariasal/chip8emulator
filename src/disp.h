#pragma once

#include "color.h"
#include "pixel_buffer.h"

struct Display : PixelBuffer<Color> {
  static constexpr auto SCREEN_WIDTH = 64;
  static constexpr auto SCREEN_HEIGHT = 32;

  Display() : PixelBuffer<Color>(SCREEN_WIDTH, SCREEN_HEIGHT, Color::WHITE) {}
};
