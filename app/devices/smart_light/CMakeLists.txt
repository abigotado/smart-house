cmake_minimum_required(VERSION 3.20)
project(smart_light)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(smart_light STATIC source/smart_light.cpp)

target_include_directories(smart_light PUBLIC include)

target_link_libraries(smart_light PUBLIC device interfaces)

target_compile_features(smart_light PUBLIC cxx_std_20) 