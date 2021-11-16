cmake_minimum_required(VERSION 3.10)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(chip8)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_library(chip8_lib)
target_sources(chip8_lib
    PRIVATE
    src/mem.cpp)
target_include_directories(chip8_lib PUBLIC src)

add_executable(chip8 src/main.cpp)
target_link_libraries(chip8 PRIVATE chip8_lib)

enable_testing()
add_subdirectory(test)
