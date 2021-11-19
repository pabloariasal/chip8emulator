#include <SDL.h>

#include <fstream>
#include <iostream>

#include "display.h"
#include "mem.h"
#include "sdl_screen.h"

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

  auto bitmap = initializeBitmap(64, 32, Color::WHITE);
  auto screen = SDLScreen(25, bitmap);

  bitmap.data.front() = Color::BLACK;
  bitmap.data.back() = Color::BLACK;

  SDL_Event event;

  while (true) {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) break;
    screen.render(bitmap);
  }

  return 0;
}
