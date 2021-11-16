#include <SDL.h>

#include <fstream>
#include <iostream>

#include "display.h"
#include "mem.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "usage "
              << "program <rom>\n";
    exit(1);
  }

  std::ifstream is(argv[1], std::ifstream::binary);
  if (!is) {
    std::cout << "could not open file " << argv[1] << '\n';
    exit(1);
  }

  Memory mem;
  mem.loadROM(is);

  Display dis{25, 64, 32};
  std::vector<uint32_t> v(64 * 32);
  v[0] = 0x0000ff00;
  v.back() = 0xff000000;

  SDL_Event event;

  while (true) {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) break;
    dis.update(v);
  }

  return 0;
}
