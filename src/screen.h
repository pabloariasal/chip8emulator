#pragma once

#include <vector>

#include "color.h"

class Screen {
 public:
  Screen() = default;
  virtual ~Screen() = default;

  Screen(const Screen&) = delete;
  Screen& operator=(const Screen&) = delete;
  Screen(Screen&&) = delete;
  Screen& operator=(Screen&&) = delete;

  virtual void render(const std::vector<Color>&) = 0;
};