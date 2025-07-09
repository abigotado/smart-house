cmake_minimum_required(VERSION 3.20)
project(smart_house_app)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Утилиты
add_subdirectory(temperature_manager)

# Общие интерфейсы и базовые классы
add_subdirectory(shared)

# Устройства (включая базовый класс)
add_subdirectory(devices)

# Управление
add_subdirectory(speaker)
add_subdirectory(home) 