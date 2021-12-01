#pragma once

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

#include "color.h"

class SDLWindow {
 public:
  SDLWindow(int width, int height);
  ~SDLWindow();

  SDLWindow(const SDLWindow&) = delete;
  SDLWindow& operator=(const SDLWindow&) = delete;
  SDLWindow(SDLWindow&&) = delete;
  SDLWindow& operator=(SDLWindow&&) = delete;

  void render(const Color* data, int width);

 private:
  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
  SDL_Texture* texture_ = nullptr;
};
