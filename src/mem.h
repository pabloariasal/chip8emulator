#pragma once

#include <cstdint>
#include <istream>
#include <vector>

class Memory {
 public:
  Memory() : mem_(4096, 0) {}
  using Index = uint16_t;
  using Word = uint8_t;

  constexpr static auto MEM_SIZE = 4096;
  constexpr static Index ROM_BEGIN = 0x200;

  bool loadROM(std::istream &istream);

  Word at(Index i) const { return mem_[i]; }

  void write(Index i, Word w) { mem_[i] = w; };
  Word read(Index i) const { return mem_[i]; };

  void dump(Index from, Index to) const;

 private:
  std::vector<Word> mem_;
};
