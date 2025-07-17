cmake_minimum_required(VERSION 3.20)
project(smart_house)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Приложение
add_subdirectory(app)

# Примеры (опционально) - закомментировано, пока нет CMakeLists.txt
add_subdirectory(examples)

# Тесты (опционально)
    add_subdirectory(tests)