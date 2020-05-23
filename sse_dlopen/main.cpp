#include <iostream>
#include <dlfcn.h>
#include <vector>
#include "simdlib.hpp"

int main(int argc, char** argv) {
    SimdLib simdlib(argv[1]);
    simdlib.doStuffFast();
}
