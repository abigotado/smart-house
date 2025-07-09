cmake_minimum_required(VERSION 3.20)
project(interfaces)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Интерфейсы как header-only библиотеки
add_library(interfaces INTERFACE)

target_include_directories(interfaces INTERFACE include)

target_compile_features(interfaces INTERFACE cxx_std_20) 