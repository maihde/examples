#ifndef H_SIMDLIB
#define H_SIMDLIB
#include <iostream>
#include <string>
#include "simdimpl.hpp"

class SimdLib {
public:
    SimdLib();

    SimdLib(const std::string& simdimpl);

    virtual ~SimdLib();
    
    void doStuffFast();
private:
    SimdImpl* impl;
    void *handle;
};
#endif