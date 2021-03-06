#include "timer.h"

#include <cmath>

constexpr auto FREQUENCY_MS = 1000 / 60;

void Timer::reset(int number_of_ticks) {
  total_ = number_of_ticks;
  count_ = number_of_ticks;
  last_update_ = std::chrono::steady_clock::now();
}

void Timer::update() {
  if (done()) {
    return;
  }
  auto now = std::chrono::steady_clock::now();
  auto elapsed_ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(now - last_update_)
          .count();
  int number_of_ticks = elapsed_ms / FREQUENCY_MS;
  count_ = std::max(0, total_ - number_of_ticks);
}

int Timer::get() const { return count_; }

bool Timer::done() const { return get() <= 0; }
bool Timer::running() const { return get() > 0; }
