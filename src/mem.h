#pragma once

#include <cstdint>
#include <istream>
#include <vector>

class Memory {
 public:
  using Index = uint16_t;
  using Word = uint8_t;

  constexpr static auto MEM_SIZE = 4096;
  constexpr static Index ROM_BEGIN = 0x200;
  constexpr static Index FONTS_BEGIN = 0x50;
  constexpr static Index FONT_SPRITE_WIDTH = 5;
  constexpr static Index FONTS_LENGTH = 16;

  Memory();

  bool loadROM(std::istream& istream);
  void loadFonts();
  void write(Index i, Word w) { mem_[i] = w; };
  Word read(Index i) const { return mem_[i]; };

  void dump(Index from, Index to) const;

 private:
  std::vector<Word> mem_;
};

std::vector<Memory::Word> readN(const Memory& mem, Memory::Index w, int n);
