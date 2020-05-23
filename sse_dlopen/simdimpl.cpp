#include <iostream>
#include "simdimpl.hpp"

class SimdConcrete : public SimdImpl {
public:
    SimdConcrete();
    virtual void doStuffFast();
};

SimdConcrete::SimdConcrete() {
        std::cout << "This is SIMD Lib" << std::endl;
#ifdef __AVX2__
        std::cout << "Oh Hi this is AVX2" << std::endl;
#elif __AVX__
        std::cout << "Oh Hi this is AVX" << std::endl;
#elif __SSE3__
        std::cout << "Oh Hi this is SSE3" << std::endl;
#elif __SSE2__
        std::cout << "Oh Hi this is SSE2" << std::endl;
#endif
}
    
void SimdConcrete::doStuffFast() {
#ifdef __AVX2__
        std::cout << "Im AVX2 Fast!" << std::endl;
#elif __AVX__
        std::cout << "Im AVX Fast!" << std::endl;
#elif __SSE3__
        std::cout << "Im SSE3 Fast!" << std::endl;
#elif __SSE2__
        std::cout << "Im SSE2 Fast!" << std::endl;
#endif      
}

extern "C" SimdImpl* build_impl() {
        return new SimdConcrete();
}