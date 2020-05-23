cmake_minimum_required(VERSION 2.6.0)
project (simdtest)

add_executable(simdtest main.cpp isimdlib.hpp)
target_link_libraries(simdtest dl)

add_library(simdlib_common SHARED simdlib_loader.cpp isimdlib.hpp)

add_library(simdlib_sse2 SHARED simdlib_loader.cpp isimdlib.hpp)
target_compile_options(simdlib_sse2 PRIVATE "-msse2")

add_library(simdlib_sse3 SHARED simdlib_loader.cpp isimdlib.hpp)
target_compile_options(simdlib_sse3 PRIVATE "-msse3")

# Will need a check compiler flag here
add_library(simdlib_avx SHARED simdlib_loader.cpp isimdlib.hpp)
target_compile_options(simdlib_avx PRIVATE "-mavx")

add_library(simdlib_avx2 SHARED simdlib_loader.cpp isimdlib.hpp)
target_compile_options(simdlib_avx2 PRIVATE "-mavx2")

