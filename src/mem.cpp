#include "mem.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

constexpr std::array<Memory::Word, Memory::FONT_SPRITE_WIDTH * Memory::FONTS_LENGTH> FONTS{
    0xF0, 0x90, 0x90, 0x90, 0xF0,  // 0
    0x20, 0x60, 0x20, 0x20, 0x70,  // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0,  // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0,  // 3
    0x90, 0x90, 0xF0, 0x10, 0x10,  // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0,  // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0,  // 6
    0xF0, 0x10, 0x20, 0x40, 0x40,  // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0,  // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0,  // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90,  // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0,  // B
    0xF0, 0x80, 0x80, 0x80, 0xF0,  // C
    0xE0, 0x90, 0x90, 0x90, 0xE0,  // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0,  // E
    0xF0, 0x80, 0xF0, 0x80, 0x80   // F
};

Memory::Memory() : mem_(MEM_SIZE, 0) {}

bool Memory::loadROM(std::istream& is) {
  // get length of stream
  is.seekg(0, is.end);
  size_t length = is.tellg();
  is.seekg(0, is.beg);

  std::vector<char> b(length);
  is.read(b.data(), length);

  if (!is) {
    std::cout << "error: only " << is.gcount() << " could be read";
    return false;
  }

  std::copy(std::cbegin(b), std::cend(b), std::begin(mem_) + ROM_BEGIN);
  return true;
}

void Memory::dump(Index from, Index to) const {
  auto to_ = std::min(static_cast<size_t>(to), mem_.size());
  for (Index i = from; i < to_; ++i) {
    printf("0x%04x %02x\n", i, mem_[i]);
  }
}

void Memory::loadFonts() {
  std::copy(FONTS.cbegin(), FONTS.cend(), std::begin(mem_) + FONTS_BEGIN);
}

std::vector<Memory::Word> readN(const Memory& mem, Memory::Index i, int n) {
  std::vector<Memory::Word> res;
  res.reserve(n);
  const auto begin = i;
  const auto end = i + n;
  for (int i = begin; i < end; ++i) {
    res.push_back(mem.read(i));
  }
  return res;
}
