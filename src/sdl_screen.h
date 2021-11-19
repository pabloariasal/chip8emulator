#pragma once

#include "screen.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class SDLScreen : public Screen {
 public:
  SDLScreen(float scale, const Bitmap& bitmap);
  SDLScreen(float scale, int width, int height);
  ~SDLScreen() override;

  void render(const Bitmap&) override;

 private:
  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
  SDL_Texture* texture_ = nullptr;
};
