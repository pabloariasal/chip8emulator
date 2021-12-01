#include "runner.h"

#include <SDL.h>

#include <fstream>
#include <iostream>

#include "game.h"
#include "process_instruction.h"
#include "sdl_window.h"

Runner::Runner() { SDL_Init(SDL_INIT_VIDEO); }

void Runner::run(const std::filesystem::path& rom) {
  auto game = Game{rom};
  auto window = SDLWindow(game.screen().width, game.screen().height);

  while (true) {
    if (!handleEvents(game)) {
      break;
    }
    if (game.next()) {
      window.render(game.screen().data, game.screen().width);
    }
  }
}

bool Runner::handleEvents(Game& game) {
  (void)game;
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        return false;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_LEFT:
            break;
          case SDLK_RIGHT:
            break;
          case SDLK_UP:
            break;
          case SDLK_DOWN:
            break;
        }
        break;
    }
  }
  return true;
}

Runner::~Runner() { SDL_Quit(); }
