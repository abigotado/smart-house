# Тесты для Smart House

Этот каталог содержит тесты для системы умного дома.

## Структура тестов

```
tests/
├── test_performance.cpp         # Тесты производительности и многопоточности
├── README.md                    # Этот файл
└── unit_tests/                  # Модульные тесты
    ├── test_smart_home_fast.cpp # Быстрые тесты SmartHome
    └── devices/                 # Тесты устройств
        ├── test_smart_light.cpp
        ├── test_thermometer.cpp
        ├── test_vacuum_cleaner.cpp
        └── test_smart_kettle.cpp
```

## Типы тестов

### 1. Модульные тесты (unit_tests/)
Быстрые тесты отдельных компонентов без асинхронных задержек.

**Преимущества:**
- Выполняются мгновенно
- Тестируют конкретную функциональность
- Идеальны для разработки и отладки

**Команды:**
```bash
# Тест SmartHome
./build/tests/unit_tests/test_smart_home_fast

# Тесты устройств
./build/tests/unit_tests/devices/test_smart_light
./build/tests/unit_tests/devices/test_thermometer
./build/tests/unit_tests/devices/test_vacuum_cleaner
./build/tests/unit_tests/devices/test_smart_kettle
```

### 2. Тесты производительности (test_performance.cpp)
Проверяют масштабируемость, многопоточность и производительность системы.

**Проверяет:**
- Создание множества устройств и колонок
- Многопоточные операции
- Утечки памяти
- Производительность UUID генерации

**Команда:**
```bash
./build/tests/test_performance
```

## Сборка тестов

```bash
# Собрать все тесты
cmake -S . -B build
cmake --build build

# Собрать конкретные тесты
cmake --build build --target test_performance
cmake --build build --target test_smart_home_fast
cmake --build build --target test_smart_light
cmake --build build --target test_thermometer
cmake --build build --target test_vacuum_cleaner
```

## Запуск всех тестов

```bash
# Через CTest
ctest --test-dir build

# Или запустить каждый тест отдельно
./build/tests/test_performance
./build/tests/unit_tests/test_smart_home_fast
./build/tests/unit_tests/devices/test_smart_light
./build/tests/unit_tests/devices/test_thermometer
./build/tests/unit_tests/devices/test_vacuum_cleaner
./build/tests/unit_tests/devices/test_smart_kettle
```

## Результаты тестирования

### Модульные тесты
- **SmartHome**: 23 проверки ✅
- **SmartLight**: 27 проверок ✅
- **Thermometer**: 25 проверок ✅
- **VacuumCleaner**: 17 проверок ✅

### Тесты производительности
- **Performance**: 21 проверка ✅
- **Thread Safety**: Все проверки ✅

## Добавление новых тестов

1. Создайте файл теста в соответствующей папке
2. Добавьте тест в CMakeLists.txt
3. Убедитесь, что тест проходит

### Пример для нового устройства:

```cpp
// tests/unit_tests/devices/test_new_device.cpp
#include <catch2/catch_test_macros.hpp>
#include "../../../app/devices/new_device/include/new_device.h"

using namespace smart_house;

TEST_CASE("NewDevice basic functionality", "[new_device]") {
    NewDevice device("Тестовое устройство");
    
    SECTION("Initial state") {
        REQUIRE(device.get_name() == "Тестовое устройство");
        REQUIRE(!device.get_id().empty());
    }
    
    // Добавьте другие тесты...
}
```

## Примечания

- Модульные тесты не содержат асинхронных задержек для быстрого выполнения
- Тесты производительности могут занимать больше времени
- Все тесты используют Catch2 framework
- Структура тестов соответствует архитектуре приложения 