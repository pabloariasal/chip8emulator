#pragma once

#include "opcode.h"
#include "state.h"

Opcode nextOpcode(State& state);
void processInstruction(Opcode opcode, State& state);
