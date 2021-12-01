#include "sdl_window.h"

#include <SDL.h>

SDLWindow::SDLWindow(int width, int height) {
  constexpr auto scale = 25;
  window_ = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, scale * width,
                             scale * height, SDL_WINDOW_SHOWN);
  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
  texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888,
                               SDL_TEXTUREACCESS_STATIC, width, height);
}

void SDLWindow::render(const Color* data, int width) {
  SDL_UpdateTexture(texture_, nullptr, data, sizeof(Color) * width);
  SDL_RenderClear(renderer_);
  SDL_RenderCopy(renderer_, texture_, NULL, NULL);
  SDL_RenderPresent(renderer_);
}

SDLWindow::~SDLWindow() {
  SDL_DestroyTexture(texture_);
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
}
