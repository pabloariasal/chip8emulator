#include <SDL.h>

#include <fstream>
#include <iostream>

#include "process_instruction.h"
#include "sdl_screen.h"
#include "state.h"

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

  auto state = State{};
  state.display.data().front() = Color::BLACK;
  state.display.data()[63] = Color::BLACK;
  state.display.data()[31 * 64] = Color::BLACK;
  state.display.data().back() = Color::BLACK;

  auto screen = SDLScreen(25, state.display.width(), state.display.height());

  SDL_Event event;

  while (true) {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) break;

    processInstruction(nextOpcode(state), state);
    screen.render(state.display.data());
  }

  return 0;
}
