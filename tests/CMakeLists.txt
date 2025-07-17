cmake_minimum_required(VERSION 3.20)
project(tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем Catch2 через FetchContent
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.4
)
FetchContent_MakeAvailable(Catch2)

# Тест производительности и многопоточности
add_executable(test_performance test_performance.cpp)

target_include_directories(test_performance PRIVATE
    ../app/home/include
    ../app/speaker/include
    ../app/devices/device/include
    ../app/devices/vacuum_cleaner/include
    ../app/devices/smart_light/include
    ../app/devices/thermometer/include
    ../app/devices/smart_kettle/include
    ../app/shared/include
    ../app/temperature_manager/include
)

target_link_libraries(test_performance
    home
    speaker
    vacuum_cleaner
    smart_light
    thermometer
    smart_kettle
    device
    shared
    temperature_manager
    Catch2::Catch2WithMain
)

# Включение модульных тестов
add_subdirectory(unit_tests)

# Запускаем тесты
include(CTest)
include(Catch)
catch_discover_tests(test_performance) 