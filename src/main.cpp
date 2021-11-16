#include <fstream>
#include <iostream>

#include "mem.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "usage "
              << "program <rom>\n";
    exit(1);
  }

  std::ifstream is(argv[1], std::ifstream::binary);
  if (!is) {
    std::cout << "could not open file " << argv[1] << '\n';
    exit(1);
  }

  Memory mem;
  mem.loadROM(is);
  mem.dump();

  return 0;
}
