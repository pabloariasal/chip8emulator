#include "sdl_screen.h"

#include <cassert>
#include <SDL.h>

SDLScreen::SDLScreen(float scale, int width, int height)
    : width_{width}, height_{height} {
  SDL_Init(SDL_INIT_VIDEO);
  window_ = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, scale * width,
                             scale * height, SDL_WINDOW_SHOWN);
  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
  texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888,
                               SDL_TEXTUREACCESS_STATIC, width, height);
}

SDLScreen::~SDLScreen() {
  SDL_DestroyTexture(texture_);
  texture_ = nullptr;
  SDL_DestroyRenderer(renderer_);
  renderer_ = nullptr;
  SDL_DestroyWindow(window_);
  window_ = nullptr;
  SDL_Quit();
}

void SDLScreen::render(const tcb::span<const Color>& data) {
  assert(static_cast<ptrdiff_t>(data.size()) == width_ * height_);
  SDL_UpdateTexture(texture_, nullptr, data.data(), sizeof(Color) * width_);
  SDL_RenderClear(renderer_);
  SDL_RenderCopy(renderer_, texture_, NULL, NULL);
  SDL_RenderPresent(renderer_);
}
