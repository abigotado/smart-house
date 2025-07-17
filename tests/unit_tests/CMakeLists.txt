# Тесты для SmartHome
add_executable(test_smart_home test_smart_home.cpp)
add_executable(test_speaker test_speaker.cpp)
add_executable(test_device test_device.cpp)
add_executable(test_temperature_manager test_temperature_manager.cpp)

target_include_directories(test_smart_home PRIVATE
    ../../app/home/include
    ../../app/speaker/include
    ../../app/devices/device/include
    ../../app/shared/include
)

target_link_libraries(test_smart_home
    home
    speaker
    device
    shared
    Catch2::Catch2WithMain
)

target_include_directories(test_speaker PRIVATE
    ../../app/speaker/include
    ../../app/devices/smart_light/include
    ../../app/devices/vacuum_cleaner/include
    ../../app/devices/device/include
    ../../app/shared/include
)

target_link_libraries(test_speaker
    speaker
    smart_light
    vacuum_cleaner
    device
    shared
    Catch2::Catch2WithMain
)

target_include_directories(test_device PRIVATE
    ../../app/devices/device/include
    ../../app/shared/include
)

target_link_libraries(test_device
    device
    shared
    Catch2::Catch2WithMain
)

target_include_directories(test_temperature_manager PRIVATE
    ../../app/temperature_manager/include
)

target_link_libraries(test_temperature_manager
    temperature_manager
    Catch2::Catch2WithMain
)

# Включение подпапок с тестами
add_subdirectory(devices)

# Добавляем тесты в CTest
include(CTest)
include(Catch)
catch_discover_tests(test_smart_home)
catch_discover_tests(test_speaker)
catch_discover_tests(test_device)
catch_discover_tests(test_temperature_manager)
 
# Здесь можно добавить другие категории тестов
# add_subdirectory(home)
# add_subdirectory(speaker)
# и т.д. 