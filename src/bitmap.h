#pragma once

#include <exception>
#include <iterator>
#include <span.hpp>

#include "pixel_buffer.h"

struct BitmapOutOfBoundsException : public std::exception {
  const char* what() const throw() override {
    return "The bitmap is out of bounds";
  }
};

// Bitmap is a non-owning view over a rectangular region of pixel data
// TODO: rename this class?
template <typename T>
class Bitmap {
 public:
  Bitmap(int width, int height, int col, int row, PixelBuffer<T>& buff)
      : width_{width}, height_{height}, col_{col}, row_{row}, buff_{buff} {
    if (width < 0 || height < 0 || row < 0 || col < 0) {
      throw BitmapOutOfBoundsException{};
    }
    // check that the view is inside the buffer's boundaries
    const auto view_top_left = std::pair<int, int>{row, col};
    const auto view_bottom_right =
        std::pair<int, int>{row + height, col + width};

    for (auto p : {view_top_left, view_bottom_right}) {
      if (p.first < 0 || p.second < 0 || p.first > buff.height() ||
          p.second > buff.width()) {
        throw BitmapOutOfBoundsException{};
      }
    }
  }

  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = typename std::iterator_traits<
        typename PixelBuffer<T>::iterator>::difference_type;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    Iterator(typename PixelBuffer<T>::iterator it, int row_width, int step)
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
    typename PixelBuffer<T>::iterator it_;
    int advanced_in_row_{0};
    int row_width_;
    int step_;
  };

  Iterator begin() {
    auto it = buff_.begin() + offset(row_, col_);
    return Iterator(it, width_, buff_.width());
  }

  Iterator end() {
    auto a = offset(row_ + height_, col_);
    auto it = buff_.begin() + a;
    return Iterator(it, width_, buff_.width());
  }

 private:
  int offset(int row, int col) const { return row * buff_.width() + col; }

  int width_;
  int height_;
  int col_;
  int row_;
  PixelBuffer<T>& buff_;
};
