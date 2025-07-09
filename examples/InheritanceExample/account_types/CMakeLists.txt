cmake_minimum_required(VERSION 3.16)
project (account_types)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(debit_account)
add_subdirectory(credit_account)
add_subdirectory(saving_account)
add_subdirectory(family_account)
