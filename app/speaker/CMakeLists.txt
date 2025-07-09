cmake_minimum_required(VERSION 3.20)
project(speaker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(speaker STATIC source/speaker.cpp)

target_include_directories(speaker PUBLIC include)

target_link_libraries(speaker PUBLIC 
    device 
    interfaces
    vacuum_cleaner
    smart_light
    thermometer
    smart_kettle
)

target_compile_features(speaker PUBLIC cxx_std_20) 