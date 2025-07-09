cmake_minimum_required(VERSION 3.16)
project(credit_account)

set(CMAKE_CXX_STANDARD 20)

add_library(credit_account STATIC source/credit_account.cpp)

target_include_directories(credit_account PUBLIC include)

target_link_libraries(credit_account PUBLIC account)