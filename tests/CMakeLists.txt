# Модульные тесты для библиотеки Smart House

# Поиск исходных файлов тестов
file(GLOB TEST_SOURCES "*.cpp")

# Создание исполняемых файлов для каждого теста
foreach(test_source ${TEST_SOURCES})
    # Получение имени файла без расширения
    get_filename_component(test_name ${test_source} NAME_WE)
    
    # Создание исполняемого файла теста
    add_executable(${test_name} ${test_source})
    
    # Линковка с основной библиотекой
    target_link_libraries(${test_name} PRIVATE SmartHouse)
    
    # Установка свойств
    set_target_properties(${test_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )
    
    # Добавление теста в CTest
    add_test(NAME ${test_name} COMMAND ${test_name})
    
    message(STATUS "Added test: ${test_name}")
endforeach()

# Создание общего тестового исполняемого файла, если есть main_test.cpp
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main_test.cpp")
    add_executable(run_all_tests main_test.cpp)
    target_link_libraries(run_all_tests PRIVATE SmartHouse)
    set_target_properties(run_all_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )
    add_test(NAME run_all_tests COMMAND run_all_tests)
    message(STATUS "Added main test runner: run_all_tests")
endif()

# Информация
message(STATUS "Tests will be built in: ${CMAKE_BINARY_DIR}/tests")
message(STATUS "Run tests with: ctest --test-dir ${CMAKE_BINARY_DIR}") 