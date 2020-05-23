Dynamically loading SIMD library sing DLOPEN
--------------------------------------------

Simple example showing how to detect the CPU 
a user has and dynamicaly load a shared object
which was built using SIMD instructions. 

Usage:
```
[ylb@micro]$ mkdir build
[ylb@micro]$ cd build
[ylb@micro]$ cmake ../
[ylb@micro]$ make -j4
[ylb@micro]$ ./simdtest ./libsimdlib_sse3.so 
HW_SSE: 1
HW_AVX2: 1
HW_AVX512F: 0
This is SIMD Lib
Oh Hi this is SSE3
Im SSE3 Fast!
```
