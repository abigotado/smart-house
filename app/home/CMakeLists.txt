cmake_minimum_required(VERSION 3.20)
project(home)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(home STATIC source/smart_home.cpp)

target_include_directories(home PUBLIC include)

target_link_libraries(home PUBLIC speaker)

target_compile_features(home PUBLIC cxx_std_20) 