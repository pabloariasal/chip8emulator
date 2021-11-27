#include "opcode.h"

uint8_t first(Opcode opcode) {
    return opcode >> 4 * 3;
}

uint8_t second(Opcode opcode) {
    opcode &= 0x0F00;
    return opcode >> 4 * 2;
}

uint8_t third(Opcode opcode) {
    opcode &= 0x00F0;
    return opcode >> 4 * 1;
}

uint8_t fourth(Opcode opcode) {
    return opcode & 0x000F;
}

uint16_t lastThree(Opcode opcode) {
    return opcode & 0x0FFF;
}

uint8_t lastTwo(Opcode opcode) {
    return opcode & 0x00FF;
}
