#include "display.h"

#include <SDL.h>

#include <cassert>

Display::Display(float scale, int width, int height) {
  SDL_Init(SDL_INIT_VIDEO);
  window_ = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, scale * width,
                             scale * height, SDL_WINDOW_SHOWN);
  renderer_ = SDL_CreateRenderer(window_, -1, 0);
  texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888,
                               SDL_TEXTUREACCESS_STREAMING, width, height);
}

Display::~Display() {
  SDL_DestroyTexture(texture_);
  texture_ = nullptr;
  SDL_DestroyRenderer(renderer_);
  renderer_ = nullptr;
  SDL_DestroyWindow(window_);
  window_ = nullptr;
  SDL_Quit();
}

void Display::update(const std::vector<uint32_t>& buffer) {
  assert(buffer.size() % 64 == 0);
  SDL_UpdateTexture(texture_, nullptr, buffer.data(), sizeof(uint32_t) * 64);
  SDL_RenderClear(renderer_);
  SDL_RenderCopy(renderer_, texture_, NULL, NULL);
  SDL_RenderPresent(renderer_);
}
