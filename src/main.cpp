#include <SDL.h>

#include <iostream>

#include "game.h"
#include "runner.h"
#include "sound.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "usage: \n"
              << "  chip8 <path-to-rom>\n";
    exit(1);
  }

  Runner().run(argv[1]);
  return 0;
}
