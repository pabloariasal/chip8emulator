#include <SDL.h>

#include <fstream>
#include <iostream>

#include "display.h"
#include "mem.h"
#include "sdl_screen.h"

constexpr auto SCREEN_WIDTH = 64;
constexpr auto SCREEN_HEIGHT = 32;

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

  std::vector<Color> display(SCREEN_WIDTH * SCREEN_HEIGHT, Color::WHITE);
  auto screen = SDLScreen(25, SCREEN_WIDTH, SCREEN_HEIGHT);

  SDL_Event event;

  while (true) {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) break;
    screen.render(display);
  }

  return 0;
}
