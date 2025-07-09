cmake_minimum_required(VERSION 3.20)
project(device)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(device STATIC source/device.cpp)

target_include_directories(device PUBLIC include)

target_compile_features(device PUBLIC cxx_std_20) 