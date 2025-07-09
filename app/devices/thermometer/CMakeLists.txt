cmake_minimum_required(VERSION 3.20)
project(thermometer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(thermometer STATIC source/thermometer.cpp)

target_include_directories(thermometer PUBLIC include)

target_link_libraries(thermometer PUBLIC device interfaces temperature_manager)

target_compile_features(thermometer PUBLIC cxx_std_20) 