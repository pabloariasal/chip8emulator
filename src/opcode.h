#pragma once

#include <inttypes.h>

using Opcode = uint16_t;

uint8_t first(Opcode opcode);
uint8_t second(Opcode opcode);
uint8_t third(Opcode opcode);
uint8_t fourth(Opcode opcode);
uint16_t lastThree(Opcode opcode);
uint8_t lastTwo(Opcode opcode);
