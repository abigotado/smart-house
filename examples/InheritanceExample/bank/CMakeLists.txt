cmake_minimum_required(VERSION 3.16)
project (bank)

set(CMAKE_CXX_STANDARD 20)

add_library(bank STATIC source/bank.cpp)

target_include_directories(bank PUBLIC include)
target_link_libraries(bank PUBLIC account)