#pragma once

#include <filesystem>

class Game;

class Runner {
 public:
  Runner();
  ~Runner();

  Runner(const Runner&) = delete;
  Runner& operator=(const Runner&) = delete;
  Runner(Runner&&) = delete;
  Runner& operator=(Runner&&) = delete;

  void run(const std::filesystem::path& rom);

 private:
  bool handleEvents(Game& game);
};
