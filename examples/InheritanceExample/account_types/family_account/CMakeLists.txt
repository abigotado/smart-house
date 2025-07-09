cmake_minimum_required(VERSION 3.16)
project(family_account)

set(CMAKE_CXX_STANDARD 20)

add_library(family_account STATIC source/family_account.cpp)

target_include_directories(family_account PUBLIC include)

target_link_libraries(family_account PUBLIC account)