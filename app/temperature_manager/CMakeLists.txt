cmake_minimum_required(VERSION 3.20)
project(temperature_manager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(temperature_manager STATIC source/temperature_manager.cpp)

target_include_directories(temperature_manager PUBLIC include)

target_compile_features(temperature_manager PUBLIC cxx_std_20) 