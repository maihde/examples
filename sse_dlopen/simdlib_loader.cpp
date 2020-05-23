#include <string>
#include <iostream>
#include <vector>
#include "isimdlib.hpp"
#include "simdlib.h"

/**
 * An example functiont that will take in C++ constructs (a vector for instance)
 * and return an instance of our SSE enabled library.
 */
extern "C" ISimdLib * print_name(double xdelta, std::vector<std::string> names) {
    return new SimdLib();
}
