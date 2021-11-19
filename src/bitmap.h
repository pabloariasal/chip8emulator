#pragma once

#include <vector>

#include "color.h"

struct Bitmap {
  int width;
  int height;
  std::vector<ColorT> data;
};
