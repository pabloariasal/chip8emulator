#pragma once

#include <chrono>

class Timer {
 public:
  void reset(int number_of_ticks);
  void update();
  int get() const;
  bool done() const;
  bool running() const;

 private:
  int count_;
  long elapsed_ms_;
  std::chrono::time_point<std::chrono::steady_clock> last_update_;
};
