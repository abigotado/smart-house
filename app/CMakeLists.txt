cmake_minimum_required(VERSION 3.20)
project(smart_house_app)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Базовые компоненты
add_subdirectory(device)
add_subdirectory(interfaces)

# Конкретные устройства
add_subdirectory(devices)

# Управление
add_subdirectory(speaker)
add_subdirectory(home) 