#include <iostream>
#include "simdlib.hpp"

#include <dlfcn.h>

#define cpuinfo(info, level)         \
  __asm__ ("cpuid\n\t"                                  \
           : "=a" (info[0]), "=b" (info[1]), "=c" (info[3]), "=d" (info[4])     \
           : "0" (level), "2" (0))



SimdLib::SimdLib() : impl(0), handle(0) {
    // auto-detect SIMD impl
    //  SIMD: 128-bit
    bool HW_SSE;
    bool HW_SSE2;
    bool HW_SSE3;
    bool HW_SSSE3;
    bool HW_SSE41;
    bool HW_SSE42;
    bool HW_SSE4a;

    //  SIMD: 256-bit
    bool HW_AVX;
    bool HW_FMA3;
    bool HW_FMA4;
    bool HW_AVX2;

    //  SIMD: 512-bit
    bool HW_AVX512F;    //  AVX512 Foundation
    bool HW_AVX512CD;   //  AVX512 Conflict Detection
    bool HW_AVX512PF;   //  AVX512 Prefetch
    bool HW_AVX512ER;   //  AVX512 Exponential + Reciprocal
    bool HW_AVX512VL;   //  AVX512 Vector Length Extensions
    bool HW_AVX512BW;   //  AVX512 Byte + Word
    bool HW_AVX512DQ;   //  AVX512 Doubleword + Quadword
    bool HW_AVX512IFMA; //  AVX512 Integer 52-bit Fused Multiply-Add
    bool HW_AVX512VBMI; //  AVX512 Vector Byte Manipulation Instructions

    int info[4];
    cpuinfo(info, 0);
    int nIds = info[0];

    cpuinfo(info, 0x80000000);
    unsigned nExIds = info[0];

    //  Detect Features
    if (nIds >= 0x00000001){
        cpuinfo(info,0x00000001);
        HW_SSE    = (info[3] & ((int)1 << 25)) != 0;
        HW_SSE2   = (info[3] & ((int)1 << 26)) != 0;
        HW_SSE3   = (info[2] & ((int)1 <<  0)) != 0;

        HW_SSSE3  = (info[2] & ((int)1 <<  9)) != 0;
        HW_SSE41  = (info[2] & ((int)1 << 19)) != 0;
        HW_SSE42  = (info[2] & ((int)1 << 20)) != 0;

        HW_AVX    = (info[2] & ((int)1 << 28)) != 0;
        HW_FMA3   = (info[2] & ((int)1 << 12)) != 0;

    }
    if (nIds >= 0x00000007){
        cpuinfo(info,0x00000007);
        HW_AVX2   = (info[1] & ((int)1 <<  5)) != 0;

        HW_AVX512F     = (info[1] & ((int)1 << 16)) != 0;
        HW_AVX512CD    = (info[1] & ((int)1 << 28)) != 0;
        HW_AVX512PF    = (info[1] & ((int)1 << 26)) != 0;
        HW_AVX512ER    = (info[1] & ((int)1 << 27)) != 0;
        HW_AVX512VL    = (info[1] & ((int)1 << 31)) != 0;
        HW_AVX512BW    = (info[1] & ((int)1 << 30)) != 0;
        HW_AVX512DQ    = (info[1] & ((int)1 << 17)) != 0;
        HW_AVX512IFMA  = (info[1] & ((int)1 << 21)) != 0;
        HW_AVX512VBMI  = (info[2] & ((int)1 <<  1)) != 0;
    }
    if (nExIds >= 0x80000001){
        cpuinfo(info,0x80000001);
        HW_SSE4a = (info[2] & ((int)1 <<  6)) != 0;
        HW_FMA4  = (info[2] & ((int)1 << 16)) != 0;
    }

    std::cout <<"HW_SSE: " << HW_SSE << std::endl;
    std::cout << "HW_AVX2: " << HW_AVX2 << std::endl;
    std::cout << "HW_AVX512F: " << HW_AVX512F << std::endl;
}

SimdLib::SimdLib(const std::string& simdimpl) : impl(0), handle(0) {
    std::cout << "Loading sharded library " << simdimpl << std::endl;

    // TODO add checks to only load handle/impl once
    // (i.e. check they are null).  You also need to check
    // that someone hasn't 
    handle = dlopen(simdimpl.c_str(), RTLD_LAZY);
    if (not handle) {
        std::cout << "Failed to open shared object" << std::endl;
    }

    SimdImpl *(*func_build_impl)(void);
    *(void**)(&func_build_impl) = dlsym(handle, "build_impl");
    if (not func_build_impl) {
        std::cout << "Failed to find the build_impl function" << std::endl;
    }

    impl = func_build_impl();
}

SimdLib::~SimdLib() {
    dlclose(handle);
}

void SimdLib::doStuffFast() {
    impl->doStuffFast();
}