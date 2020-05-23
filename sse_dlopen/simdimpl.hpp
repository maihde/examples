#ifndef H_SIMDIMPL
#define H_SIMDIMPL
#include <iostream>
class SimdImpl {
public:
    SimdImpl() {};
    virtual ~SimdImpl() {};
    virtual void doStuffFast() = 0;
};

extern "C" SimdImpl* build_impl();

#endif