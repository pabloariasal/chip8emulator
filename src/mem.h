#pragma once

#include <cstdint>
#include <istream>

class Memory {
 public:
  using Index = uint16_t;

  constexpr static auto MEM_SIZE = 4096;
  constexpr static Index ROM_BEGIN = 0x200;

  bool loadROM(std::istream &istream);

  uint8_t at(Index i) const { return mem[i]; }

  void dump() const;

 private:
  uint8_t mem[MEM_SIZE]{};
};
