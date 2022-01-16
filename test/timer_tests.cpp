#include <catch2/catch.hpp>

#include <thread>
#include "timer.h"

TEST_CASE("Timer Tests") {
  Timer timer;
  timer.reset(120); // timer runs for 2 seconds
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  timer.update();
  // check in the middle, value should be around 60
  REQUIRE(abs(timer.get() - 60) < 3);
  std::this_thread::sleep_for(std::chrono::milliseconds(1500));
  timer.update();
  // now the timer should be finished
  REQUIRE(timer.get() == 0);
  REQUIRE(timer.done());
}
