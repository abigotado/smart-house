cmake_minimum_required(VERSION 3.16)
project(SmartHouse VERSION 1.0.0 LANGUAGES CXX)

# Настройки компилятора
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Флаги компиляции для отладки и оптимизации
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Установка типа сборки по умолчанию
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Директории
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set(EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/examples)

# Поиск исходных файлов
file(GLOB_RECURSE SOURCES 
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/*.cxx"
)

file(GLOB_RECURSE HEADERS 
    "${INCLUDE_DIR}/*.h"
    "${INCLUDE_DIR}/*.hpp"
)

# Создание библиотеки
if(SOURCES)
    add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
else()
    # Создаем header-only библиотеку, если нет исходных файлов
    add_library(${PROJECT_NAME} INTERFACE)
    target_include_directories(${PROJECT_NAME} INTERFACE 
        $<BUILD_INTERFACE:${INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
    )
    target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
    message(STATUS "Creating header-only library (no .cpp files found)")
    return()
endif()

# Настройка include директорий
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        $<BUILD_INTERFACE:${INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
    PRIVATE 
        ${SRC_DIR}
)

# Компиляторные флаги для библиотеки
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Опция для сборки примеров
option(BUILD_EXAMPLES "Build example programs" ON)

# Опция для сборки тестов
option(BUILD_TESTS "Build unit tests" ON)

# Сборка примеров
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Сборка тестов
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Установка библиотеки
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Установка заголовочных файлов
install(DIRECTORY ${INCLUDE_DIR}/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

# Экспорт конфигурации
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake/${PROJECT_NAME}
)

# Информация о проекте
message(STATUS "=== Smart House Library Configuration ===")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build examples: ${BUILD_EXAMPLES}")
message(STATUS "Build tests: ${BUILD_TESTS}")
message(STATUS "========================================") 