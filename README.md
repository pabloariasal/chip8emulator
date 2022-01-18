# C++ CHIP-8 Emulator

[CHIP-8](https://en.wikipedia.org/wiki/CHIP-8) emulator written in C++17

* SDL2
* Sound
* Fully tested

# Screenshots

## Space Invaders
![](screenshots/space_invaders1.png)
![](screenshots/space_invaders2.png)

## Pong
![](screenshots/pong.png)

# Test ROM
![](screenshots/test.png)
Taken from: https://github.com/corax89/chip8-test-rom

# Build

```sh
mkdir build
cmake -Bbuild .
cmake --build build
```

# Run a ROM / Play a game

```sh
./build/chip8 <path-to-rom>
```

# Running the Tests
```sh
ctest --test-dir build
```
```
Test project /home/pablo/workspace/chip8emulator/build
      Start  1: Memory Tests
 1/16 Test  #1: Memory Tests ..............................   Passed    0.01 sec
      Start  2: PixelBuffer Tests
 2/16 Test  #2: PixelBuffer Tests .........................   Passed    0.01 sec
      Start  3: Next Opcode Tests
 3/16 Test  #3: Next Opcode Tests .........................   Passed    0.01 sec
      Start  4: FX55/FX65 Memory Read Write
 4/16 Test  #4: FX55/FX65 Memory Read Write ...............   Passed    0.02 sec
      Start  5: 6XNN/7XNN/ANNN - Registers
 5/16 Test  #5: 6XNN/7XNN/ANNN - Registers ................   Passed    0.01 sec
      Start  6: DXYN
 6/16 Test  #6: DXYN ......................................   Passed    0.02 sec
      Start  7: Skip Control Flow - 3XNN/4XNN/5XY0/9XY0
 7/16 Test  #7: Skip Control Flow - 3XNN/4XNN/5XY0/9XY0 ...   Passed    0.01 sec
      Start  8: 00EE/2NNN/BNNN Subroutines
 8/16 Test  #8: 00EE/2NNN/BNNN Subroutines ................   Passed    0.02 sec
      Start  9: Math/Arithmetic Intructions
 9/16 Test  #9: Math/Arithmetic Intructions ...............   Passed    0.02 sec
      Start 10: FX0A - Key Input
10/16 Test #10: FX0A - Key Input ..........................   Passed    0.02 sec
      Start 11: FX29 - Font character
11/16 Test #11: FX29 - Font character .....................   Passed    0.01 sec
      Start 12: FX33 - Decimal conversion
12/16 Test #12: FX33 - Decimal conversion .................   Passed    0.01 sec
      Start 13: FX07/FX15/FX18 - Timers
13/16 Test #13: FX07/FX15/FX18 - Timers ...................   Passed    0.01 sec
      Start 14: CXNN - Random
14/16 Test #14: CXNN - Random .............................   Passed    0.02 sec
      Start 15: Opcode Tests
15/16 Test #15: Opcode Tests ..............................   Passed    0.01 sec
      Start 16: Timer Tests
16/16 Test #16: Timer Tests ...............................   Passed    2.51 sec

100% tests passed, 0 tests failed out of 16

Total Test time (real) =   2.76 sec
```
