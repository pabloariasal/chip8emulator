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
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        return false;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_1:
            game.keyPressed(0x1);
            break;
          case SDLK_2:
            game.keyPressed(0x2);
            break;
          case SDLK_3:
            game.keyPressed(0x3);
            break;
          case SDLK_4:
            game.keyPressed(0xC);
            break;
          case SDLK_q:
            game.keyPressed(0x4);
            break;
          case SDLK_w:
            game.keyPressed(0x5);
            break;
          case SDLK_e:
            game.keyPressed(0x6);
            break;
          case SDLK_r:
            game.keyPressed(0xD);
            break;
          case SDLK_a:
            game.keyPressed(0x7);
            break;
          case SDLK_s:
            game.keyPressed(0x8);
            break;
          case SDLK_d:
            game.keyPressed(0x9);
            break;
          case SDLK_f:
            game.keyPressed(0xE);
            break;
          case SDLK_z:
            game.keyPressed(0xA);
            break;
          case SDLK_x:
            game.keyPressed(0x0);
            break;
          case SDLK_c:
            game.keyPressed(0xB);
            break;
          case SDLK_v:
            game.keyPressed(0xF);
            break;
        }
        break;
      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
          case SDLK_1:
            game.keyReleased(0x1);
            break;
          case SDLK_2:
            game.keyReleased(0x2);
            break;
          case SDLK_3:
            game.keyReleased(0x3);
            break;
          case SDLK_4:
            game.keyReleased(0xC);
            break;
          case SDLK_q:
            game.keyReleased(0x4);
            break;
          case SDLK_w:
            game.keyReleased(0x5);
            break;
          case SDLK_e:
            game.keyReleased(0x6);
            break;
          case SDLK_r:
            game.keyReleased(0xD);
            break;
          case SDLK_a:
            game.keyReleased(0x7);
            break;
          case SDLK_s:
            game.keyReleased(0x8);
            break;
          case SDLK_d:
            game.keyReleased(0x9);
            break;
          case SDLK_f:
            game.keyReleased(0xE);
            break;
          case SDLK_z:
            game.keyReleased(0xA);
            break;
          case SDLK_x:
            game.keyReleased(0x0);
            break;
          case SDLK_c:
            game.keyReleased(0xB);
            break;
          case SDLK_v:
            game.keyReleased(0xF);
            break;
        }
        break;
    }
  }
  return true;
}

Runner::~Runner() { SDL_Quit(); }
