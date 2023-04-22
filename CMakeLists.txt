cmake_minimum_required(VERSION 3.12)

# Cross compilation
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# which compilers to use for C and C++
set(tools ${CMAKE_SOURCE_DIR}/toolchain/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf)
set(CMAKE_C_COMPILER   ${tools}/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/arm-linux-gnueabihf-g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

project("axi_fft_test" VERSION 0.0.1)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/fmt)

add_executable(axi_fft_test src/axi_fft_test.cpp src/TestVectors/TestVectors.cpp)
target_link_libraries(axi_fft_test PRIVATE fmt::fmt)

add_executable(speedTest src/speedTest.cpp src/TestVectors/TestVectors.cpp)
target_link_libraries(speedTest PRIVATE fmt::fmt)

add_executable(axi_loopback_test src/axi_loopback_test.cpp)
