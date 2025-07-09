cmake_minimum_required(VERSION 3.16)
project(debit_account)

set(CMAKE_CXX_STANDARD 20)

add_library(debit_account STATIC source/debit_account.cpp)

target_include_directories(debit_account PUBLIC include)

target_link_libraries(debit_account PUBLIC account)