#pragma once

#include <filesystem>
#include <memory>

#include "color.h"
#include "state.h"

struct Screen {
  int width;
  int height;
  const Color* data;
};

class Game {
 public:
  Game(const std::filesystem::path& rom);

  Screen screen() const;
  // Executes the next instruction
  // Returns if the display has been invalidated
  bool next();
  void keyPressed();

 private:
  std::unique_ptr<State> state_;
};
