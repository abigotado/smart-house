cmake_minimum_required(VERSION 3.20)
project(devices)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Базовые компоненты
add_subdirectory(device)
# Интерфейсы теперь в app/shared

# Конкретные устройства
add_subdirectory(vacuum_cleaner)
add_subdirectory(smart_light)
add_subdirectory(thermometer)
add_subdirectory(smart_kettle) 