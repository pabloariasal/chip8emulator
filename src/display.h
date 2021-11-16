#pragma once

#include <inttypes.h>

#include <vector>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class Display {
 public:
  Display(float scale, int width, int height);
  ~Display();

  Display(const Display&) = delete;
  Display& operator=(const Display&) = delete;
  Display(Display&&) = delete;
  Display& operator=(Display&&) = delete;

  void update(const std::vector<uint32_t>&);

 private:
  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
  SDL_Texture* texture_ = nullptr;
};
