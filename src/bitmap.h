#pragma once

#include <iterator>
#include <span.hpp>

#include "pixel_buffer.h"

// Bitmap is a non-owning view over a rectangular region of pixel data
template <typename T>
class Bitmap {
 public:
  Bitmap(int width, int height, int col, int row, PixelBuffer<T> buff)
      : width_{width}, height_{height}, col_{col}, row_{row}, buff_{buff} {
    // TODO: error handling
  }

  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = typename std::iterator_traits<
        typename PixelBuffer<T>::iterator>::difference_type;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    Iterator(typename tcb::span<T>::iterator it, int row_width, int step)
        : it_{it}, advanced_in_row_{0}, row_width_{row_width}, step_{step} {}

    reference operator*() const { return *it_; }
    pointer operator->() { return &(*it_); }

    Iterator& operator++() {
      if (advanced_in_row_ < row_width_ - 1) {
        ++it_;
        advanced_in_row_++;
      } else {
        it_ += step_ - (row_width_ - 1);
        advanced_in_row_ = 0;
      }
      return *this;
    }

    // Postfix increment
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    friend bool operator==(const Iterator& a, const Iterator& b) {
      return a.it_ == b.it_;
    };

    friend bool operator!=(const Iterator& a, const Iterator& b) {
      return a.it_ != b.it_;
    };

   private:
    typename tcb::span<T>::iterator it_;
    int advanced_in_row_{0};
    int row_width_;
    int step_;
  };

  Iterator begin() {
    auto it = buff_.data.begin() + offset(row_, col_);
    return Iterator(it, width_, buff_.elementsPerRow);
  }

  Iterator end() {
    auto a = offset(row_ + height_, col_);
    auto it = buff_.data.begin() + a;
    return Iterator(it, width_, buff_.elementsPerRow);
  }

 private:
  int offset(int row, int col) const {
    return row * buff_.elementsPerRow + col;
  }

  int width_;
  int height_;
  int col_;
  int row_;
  PixelBuffer<T> buff_;
};
