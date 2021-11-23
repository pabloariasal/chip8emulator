#pragma once

#include <span.hpp>

template <typename T>
struct PixelBuffer {
  using iterator = typename tcb::span<T>::iterator;

  int elementsPerRow{};
  tcb::span<T> data;
};
