#ifndef H_SIMDLIB
#define H_SIMDLIB
#include <iostream>
#include <string>

class SimdLib {
public:
    SimdLib();

    SimdLib(const std::string& simdimpl);

    virtual ~SimdLib();
    
    void doStuffFast();
};
#endif