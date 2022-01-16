#include "game.h"

#include <fstream>
#include <iostream>

#include "process_instruction.h"
#include "state.h"

Game::Game(const std::filesystem::path& rom)
    : state_{std::make_unique<State>()} {
  std::ifstream is(rom, std::ifstream::binary);
  if (!is) {
    throw std::runtime_error{"could not load rom"};
  }
  state_->mem.loadROM(is);
  is.close();

  state_->mem.loadFonts();
}

Screen Game::screen() const {
  return {state_->display.width(), state_->display.height(),
          state_->display.data().data()};
}

bool Game::next() {
  auto next_opcode = nextOpcode(*state_);
  processInstruction(next_opcode, *state_);
  updateTimers();
  // TODO: this should only be true if the screen must be redrawn
  return true;
}

void Game::keyPressed(KeyT key) {
  state_->key = key;
  std::cout << "key pressed: " << std::to_string(key) << std::endl;
}

void Game::updateTimers() {
  state_->delayTimer.update();
  state_->soundTimer.update();

  if (state_->soundTimer.running()) {
    sound_.play();
  }
  if (state_->soundTimer.done()) {
    sound_.stop();
  }
}
