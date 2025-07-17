cmake_minimum_required(VERSION 3.20)
project(SmartHouseDemo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SmartHouseDemo main.cpp)

target_include_directories(SmartHouseDemo PRIVATE
    ../../app/home/include
    ../../app/speaker/include
    ../../app/devices/device/include
    ../../app/devices/vacuum_cleaner/include
    ../../app/devices/smart_light/include
    ../../app/devices/thermometer/include
    ../../app/devices/smart_kettle/include
    ../../app/shared/include
    ../../app/temperature_manager/include
)

target_link_libraries(SmartHouseDemo
    home
    speaker
    vacuum_cleaner
    smart_light
    thermometer
    smart_kettle
    device
    shared
    temperature_manager
) 