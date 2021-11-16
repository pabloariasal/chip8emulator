#include "mem.h"

#include <iostream>
#include <vector>

void Memory::loadROM(std::istream &is) {
  // get length of stream
  is.seekg(0, is.end);
  size_t length = is.tellg();
  is.seekg(0, is.beg);

  std::vector<char> b(length);
  is.read(b.data(), length);

  if (!is) {
    std::cout << "error: only " << is.gcount() << " could be read";
  }

  std::copy(std::cbegin(b), std::cend(b), std::begin(mem) + ROM_BEGIN);
}

void Memory::dump(Index start_at) const {
  Index i{start_at};
  for (const auto &e : mem) {
    printf("0x%04x %02x\n", i++, e);
  }
}
