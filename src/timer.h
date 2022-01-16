#pragma once

#include <inttypes.h>
#include <chrono>

class Timer {
 public:
  void reset(uint8_t number_of_ticks);
  void update();
  int get() const;
  bool done() const;
  bool running() const;

 private:
  uint8_t count_;
  std::chrono::time_point<std::chrono::steady_clock> last_update_;
};
