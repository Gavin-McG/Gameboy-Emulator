#include <iostream>
#include <string>
#include "memory/memory.h"

int main(int argc, char** argv) {

    gameboy::memory mem;
    mem.write(0xC000, 0xF);

    std::cout << "Hello World!" << std::endl;
    std::cout << std::to_string(mem.read(0xC000)) << std::endl;
    return 0;
}