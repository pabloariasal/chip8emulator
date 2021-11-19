#pragma once

#include <vector>

#include "color.h"

struct Bitmap {
  int width;
  int height;
  std::vector<Color> data;

  int index(int x, int y) const { return width * x + y; }

  static Bitmap initialize(int width, int height, Color color = Color::WHITE) {
    return Bitmap{width, height, std::vector<Color>(width * height, color)};
  }

};
