cmake_minimum_required(VERSION 3.20)
project(vacuum_cleaner)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(vacuum_cleaner STATIC source/vacuum_cleaner.cpp)

target_include_directories(vacuum_cleaner PUBLIC include)

target_link_libraries(vacuum_cleaner PUBLIC device shared)

target_compile_features(vacuum_cleaner PUBLIC cxx_std_20) 