#include "timer.h"

#include <cmath>

constexpr auto FREQUENCY_MS = 1000 / 60;

void Timer::reset(uint8_t number_of_ticks) {
  count_ = number_of_ticks;
  last_update_ = std::chrono::steady_clock::now();
}

void Timer::update() {
  if (count_ <= 0) {
    return;
  }
  auto now = std::chrono::steady_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(now - last_update_)
          .count();
  auto diff = std::floor(elapsed / FREQUENCY_MS);
  count_ = count_ - diff > 0 ? count_ - diff : 0;
  last_update_ = now;
}

int Timer::get() const { return count_; }

bool Timer::done() const { return count_ <= 0; }
bool Timer::running() const { return count_ > 0; }
