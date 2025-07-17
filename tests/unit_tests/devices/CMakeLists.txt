# Тесты для устройств Smart House

include(Catch)

# Тесты для устройств
add_executable(test_smart_light test_smart_light.cpp)
add_executable(test_thermometer test_thermometer.cpp)
add_executable(test_vacuum_cleaner test_vacuum_cleaner.cpp)
add_executable(test_smart_kettle test_smart_kettle.cpp)

# Настройка для SmartLight
target_include_directories(test_smart_light PRIVATE
    ../../../app/devices/smart_light/include
    ../../../app/devices/device/include
    ../../../app/shared/include
)

target_link_libraries(test_smart_light
    smart_light
    device
    shared
    Catch2::Catch2WithMain
)

# Настройка для Thermometer
target_include_directories(test_thermometer PRIVATE
    ../../../app/devices/thermometer/include
    ../../../app/devices/device/include
    ../../../app/shared/include
    ../../../app/temperature_manager/include
)

target_link_libraries(test_thermometer
    thermometer
    device
    shared
    temperature_manager
    Catch2::Catch2WithMain
)

# Настройка для VacuumCleaner
target_include_directories(test_vacuum_cleaner PRIVATE
    ../../../app/devices/vacuum_cleaner/include
    ../../../app/devices/device/include
    ../../../app/shared/include
)

target_link_libraries(test_vacuum_cleaner
    vacuum_cleaner
    device
    shared
    Catch2::Catch2WithMain
)

# Настройка для SmartKettle
target_include_directories(test_smart_kettle PRIVATE
    ../../../app/devices/smart_kettle/include
    ../../../app/devices/device/include
    ../../../app/shared/include
    ../../../app/temperature_manager/include
)

target_link_libraries(test_smart_kettle
    smart_kettle
    device
    shared
    temperature_manager
    Catch2::Catch2WithMain
)

# Добавляем тесты в CTest
include(CTest)
include(Catch)
catch_discover_tests(test_smart_light)
catch_discover_tests(test_thermometer)
catch_discover_tests(test_vacuum_cleaner)
catch_discover_tests(test_smart_kettle)

# Информация
message(STATUS "Device tests will be built in: ${CMAKE_BINARY_DIR}/tests/unit_tests/devices") 