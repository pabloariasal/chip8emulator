#pragma once

#include "screen.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class SDLScreen : public Screen {
 public:
  SDLScreen(float scale, int width, int height);
  ~SDLScreen() override;

  void render(const tcb::span<const Color>& data) override;

 private:
  int width_;
  int height_;

  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
  SDL_Texture* texture_ = nullptr;
};
