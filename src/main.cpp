#include <SDL.h>

#include <filesystem>
#include <fstream>
#include <iostream>

#include "process_instruction.h"
#include "sdl_screen.h"
#include "state.h"

namespace {

State startGame(const std::filesystem::path& rom) {
  State state{};

  std::ifstream is(rom, std::ifstream::binary);
  if (!is) {
    std::cout << "could not open file " << rom << '\n';
    exit(1);
  }
  state.mem.loadROM(is);
  is.close();
  return state;
}
}  // namespace

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "usage "
              << "program <rom>\n";
    exit(1);
  }

  auto state = startGame(argv[1]);
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
