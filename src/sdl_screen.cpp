#include "sdl_screen.h"

#include <SDL.h>

SDLScreen::SDLScreen(float scale, const Bitmap& bitmap)
    : SDLScreen(scale, bitmap.width, bitmap.height) {}

SDLScreen::SDLScreen(float scale, int width, int height) {
  // TODO: implement proper error handling
  SDL_Init(SDL_INIT_VIDEO);
  window_ = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, scale * width,
                             scale * height, SDL_WINDOW_SHOWN);
  renderer_ = SDL_CreateRenderer(window_, -1, 0);
  texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888,
                               SDL_TEXTUREACCESS_STREAMING, width, height);
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

void SDLScreen::render(const Bitmap& bitmap) {
  SDL_UpdateTexture(texture_, nullptr, bitmap.data.data(),
                    sizeof(ColorT) * bitmap.width);
  SDL_RenderClear(renderer_);
  SDL_RenderCopy(renderer_, texture_, NULL, NULL);
  SDL_RenderPresent(renderer_);
}
