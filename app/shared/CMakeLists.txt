cmake_minimum_required(VERSION 3.20)
project(shared)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(shared STATIC source/uuid.cpp)

target_include_directories(shared PUBLIC include)

target_compile_features(shared PUBLIC cxx_std_20) 