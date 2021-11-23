find_package(Catch2 2.13.7 REQUIRED)

add_executable(memory_tests memory_tests.cpp)
target_link_libraries(memory_tests PRIVATE Catch2::Catch2WithMain chip8_lib)

add_executable(bitmap_tests bitmap_tests.cpp)
target_link_libraries(bitmap_tests PRIVATE Catch2::Catch2WithMain chip8_lib)

add_executable(display_tests display_tests.cpp)
target_link_libraries(display_tests PRIVATE Catch2::Catch2WithMain chip8_lib)

include(CTest)
include(Catch)
catch_discover_tests(memory_tests)
catch_discover_tests(bitmap_tests)
catch_discover_tests(display_tests)
