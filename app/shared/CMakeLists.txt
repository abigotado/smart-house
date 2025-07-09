cmake_minimum_required(VERSION 3.20)
project(shared)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Общие интерфейсы и базовые классы как header-only библиотека
add_library(shared INTERFACE)

target_include_directories(shared INTERFACE include)

target_compile_features(shared INTERFACE cxx_std_20) 