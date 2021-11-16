#pragma once

#include <cstdint>
#include <istream>

class Memory {
 public:
  using Index = uint16_t;

  constexpr static Index ROM_BEGIN = 0x200;

  void loadROM(std::istream &istream);

  uint8_t at(Index i) const { return mem[i]; }

  void dump(Index start_at) const;

 private:
  uint8_t mem[4096]{};
};
