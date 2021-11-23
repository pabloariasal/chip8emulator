#pragma once

#include "screen.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class SDLScreen : public Screen {
 public:
  SDLScreen(float scale, int width, int height);
  ~SDLScreen() override;

  void render(const std::vector<Color>&) override;

 private:
  std::size_t width_;
  std::size_t height_;

  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
  SDL_Texture* texture_ = nullptr;
};
