cmake_minimum_required(VERSION 3.20)
project(smart_kettle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(smart_kettle STATIC source/smart_kettle.cpp)

target_include_directories(smart_kettle PUBLIC include)

target_link_libraries(smart_kettle PUBLIC device shared temperature_manager)

target_compile_features(smart_kettle PUBLIC cxx_std_20) 