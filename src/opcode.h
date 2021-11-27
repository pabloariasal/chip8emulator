#pragma once

#include <inttypes.h>

using Opcode = uint16_t;
using Nibble = uint8_t;

inline Nibble first(Opcode opcode) {
    return opcode >> 4 * 3;
}

inline Nibble second(Opcode opcode) {
    opcode &= 0x0F00;
    return opcode >> 2 * 4;
}

inline Nibble third(Opcode opcode) {
    opcode &= 0x00F0;
    return opcode >> 3 * 4;
}

inline Nibble fourth(Opcode opcode) {
    return opcode & 0x000F;
}
