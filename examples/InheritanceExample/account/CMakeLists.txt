cmake_minimum_required(VERSION 3.16)
project(account)

set(CMAKE_CXX_STANDARD 20)

add_library(account INTERFACE)

target_include_directories(account INTERFACE include)