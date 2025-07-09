cmake_minimum_required(VERSION 3.16)
project(saving_account)

set(CMAKE_CXX_STANDARD 20)

add_library(saving_account STATIC source/saving_account.cpp)

target_include_directories(saving_account PUBLIC include)

target_link_libraries(saving_account PUBLIC account)