find_package(Catch2 2.13.7 REQUIRED)

add_executable(chip8tests test.cpp)
target_link_libraries(chip8tests PRIVATE Catch2::Catch2WithMain chip8_lib)

include(CTest)
include(Catch)
catch_discover_tests(chip8tests)
