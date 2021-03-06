#pragma once

#include <cassert>
#include <vector>

#include "span.hpp"

template <typename T>
class PixelBuffer {
 public:
  using iterator = typename std::vector<T>::iterator;

  PixelBuffer(int row_width, std::vector<T>&& data)
      : row_width_{row_width}, data_{std::move(data)} {
    assert(row_width == 0 || data.size() / row_width == 0);
  }

  PixelBuffer(int width, int height, T c)
      : row_width_{width}, data_(width * height, c) {}

  int width() const { return row_width_; }
  int height() const { return data_.empty() ? 0 : data_.size() / row_width_; }

  const T& get(int row, int col) const { return data_.at(index(row, col)); }
  T& get(int row, int col) { return data_.at(index(row, col)); }

  tcb::span<const T> data() const { return data_; }

  void setAll(const T& e) { std::fill(data_.begin(), data_.end(), e); }

  typename std::vector<T>::iterator begin() { return data_.begin(); }
  typename std::vector<T>::iterator end() { return data_.end(); }
  typename std::vector<T>::const_iterator cbegin() const {
    return data_.cbegin();
  }
  typename std::vector<T>::const_iterator cend() const { return data_.cend(); }

 private:
  std::size_t index(int row, int col) const { return row * row_width_ + col; }

  int row_width_;
  std::vector<T> data_;
};
