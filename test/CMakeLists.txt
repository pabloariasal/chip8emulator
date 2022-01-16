find_package(Catch2 2.13.7 REQUIRED)

add_executable(memory_tests memory_tests.cpp)
target_link_libraries(memory_tests PRIVATE Catch2::Catch2WithMain chip8_lib)

add_executable(pixel_buffer_tests pixel_buffer_tests.cpp)
target_link_libraries(pixel_buffer_tests PRIVATE Catch2::Catch2WithMain chip8_lib)

add_executable(instruction_tests instruction_tests.cpp)
target_link_libraries(instruction_tests PRIVATE Catch2::Catch2WithMain chip8_lib)

add_executable(opcode_tests opcode_tests.cpp)
target_link_libraries(opcode_tests PRIVATE Catch2::Catch2WithMain chip8_lib)

add_executable(timer_tests timer_tests.cpp)
target_link_libraries(timer_tests PRIVATE Catch2::Catch2WithMain chip8_lib)

include(CTest)
include(Catch)
catch_discover_tests(memory_tests)
catch_discover_tests(pixel_buffer_tests)
catch_discover_tests(instruction_tests)
catch_discover_tests(opcode_tests)
catch_discover_tests(timer_tests)
