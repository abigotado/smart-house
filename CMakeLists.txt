cmake_minimum_required(VERSION 3.20)
project(smart_house)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Приложение
add_subdirectory(app)

# Примеры (опционально)
add_subdirectory(examples)

# Тесты (опционально)
add_subdirectory(tests) 