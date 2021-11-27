cmake_minimum_required(VERSION 3.10)

project(chip8emulator)

#####################################################
# Conan
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
                TLS_VERIFY ON)
endif()
include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_configure(REQUIRES
                          catch2/2.13.7
                          sdl/2.0.16
                      GENERATORS cmake_find_package
                      OPTIONS catch2:with_main=True)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    SETTINGS ${settings})

#####################################################
# Dependencies
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
find_package(SDL2 2.0.16 REQUIRED)

#####################################################
# Library
# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_library(chip8_lib)
target_sources(chip8_lib
    PRIVATE
    src/mem.cpp
    src/draw_sprite.cpp
    src/sdl_screen.cpp
    src/opcode.cpp
    src/inst.cpp
    src/process_instruction.cpp
    )
target_include_directories(chip8_lib PUBLIC src 3rdparty)
target_link_libraries(chip8_lib PUBLIC SDL2::SDL2)

add_executable(chip8 src/main.cpp)
target_link_libraries(chip8 PRIVATE chip8_lib)

#####################################################
# Tests
enable_testing()
add_subdirectory(test)
