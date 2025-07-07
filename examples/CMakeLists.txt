# Примеры для демонстрации использования библиотеки Smart House

# Поиск исходных файлов для демонстрационных программ
file(GLOB EXAMPLE_SOURCES "*.cpp")

# Создание исполняемых файлов для каждой демонстрационной программы
foreach(example_source ${EXAMPLE_SOURCES})
    # Получение имени файла без расширения
    get_filename_component(example_name ${example_source} NAME_WE)
    
    # Создание исполняемого файла для демонстрационной программы
    add_executable(${example_name} ${example_source})
    
    # Линковка с основной библиотекой Smart House
    target_link_libraries(${example_name} PRIVATE SmartHouse)
    
    # Установка свойств исполняемого файла
    set_target_properties(${example_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples
    )
    
    message(STATUS "Added example: ${example_name}")
endforeach()

# Информация о том, в какой директории будут созданы исполняемые файлы
message(STATUS "Examples will be built in: ${CMAKE_BINARY_DIR}/examples") 