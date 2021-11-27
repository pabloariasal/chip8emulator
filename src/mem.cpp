#include "mem.h"

#include <algorithm>
#include <iostream>
#include <vector>

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

std::vector<Memory::Word> readN(const Memory& mem, Memory::Index w, int n) {
  std::vector<Memory::Word> res;
  res.reserve(n);
  const auto begin = w;
  const auto end = w + n;
  for (int i = begin; i < end; ++i) {
    res.push_back(mem.read(i));
  }
  return res;
}
