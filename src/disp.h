#pragma once

#include "color.h"
#include "pixel_buffer.h"

constexpr auto SCREEN_WIDTH = 64;
constexpr auto SCREEN_HEIGHT = 32;

struct Display : PixelBuffer<Color> {
  Display() : PixelBuffer<Color>(SCREEN_WIDTH, SCREEN_HEIGHT, Color::WHITE) {}
};
