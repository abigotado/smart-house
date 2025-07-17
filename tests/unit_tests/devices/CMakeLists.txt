# Тесты для устройств Smart House

include(Catch)

# Поиск исходных файлов тестов устройств
file(GLOB DEVICE_TEST_SOURCES "*.cpp")

# Создание исполняемых файлов для каждого теста устройства
foreach(test_source ${DEVICE_TEST_SOURCES})
    # Получение имени файла без расширения
    get_filename_component(test_name ${test_source} NAME_WE)
    
    # Создание исполняемого файла теста
    add_executable(${test_name} ${test_source})
    
    # Добавление путей включения
    target_include_directories(${test_name} PRIVATE 
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/app
    )
    
    # Линковка с библиотеками устройств и Catch2
    target_link_libraries(${test_name} PRIVATE 
        smart_kettle
        smart_light
        thermometer
        vacuum_cleaner
        device
        shared
        temperature_manager
        Catch2::Catch2WithMain
    )
    
    # Установка свойств
    set_target_properties(${test_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests/unit_tests/devices
    )
    
    # Добавление теста в CTest через Catch2
    catch_discover_tests(${test_name})
    
    message(STATUS "Added device test: ${test_name}")
endforeach()

# Информация
message(STATUS "Device tests will be built in: ${CMAKE_BINARY_DIR}/tests/unit_tests/devices") 