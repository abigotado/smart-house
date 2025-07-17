# Тесты для Smart House

Эта папка содержит все тесты для библиотеки Smart House.

## Структура

```
tests/
├── CMakeLists.txt              # Основной CMake файл для тестов
├── README.md                   # Этот файл
└── unit_tests/                 # Модульные тесты
    ├── CMakeLists.txt          # CMake файл для модульных тестов
    └── devices/                # Тесты устройств
        ├── CMakeLists.txt      # CMake файл для тестов устройств
        └── test_smart_kettle.cpp # Тест для SmartKettle
```

## Запуск тестов

### Сборка тестов
```bash
cd build
make -j4
```

### Запуск всех тестов
```bash
cd build
ctest --test-dir .
```

### Запуск конкретного теста
```bash
cd build
./tests/unit_tests/devices/test_smart_kettle
```

## Добавление новых тестов

### Для устройств
1. Создайте файл `test_<device_name>.cpp` в папке `tests/unit_tests/devices/`
2. CMake автоматически найдет и соберет новый тест

### Для других компонентов
1. Создайте новую папку в `tests/unit_tests/` (например, `home/`, `speaker/`)
2. Добавьте `CMakeLists.txt` в новую папку
3. Обновите `tests/unit_tests/CMakeLists.txt`, добавив `add_subdirectory(новая_папка)`

## Примеры тестов

### Тест устройства
```cpp
#include "app/devices/smart_kettle/include/smart_kettle.h"
#include <iostream>

int main() {
    using namespace smart_house;
    
    SmartKettle kettle("Тестовый чайник");
    std::cout << "Создан: " << kettle.to_string() << std::endl;
    
    // Тестирование функциональности...
    
    return 0;
}
```

## Примечания

- Все тесты собираются в папку `build/tests/`
- Тесты устройств собираются в `build/tests/unit_tests/devices/`
- Используйте `ctest` для автоматического запуска всех тестов
- Каждый тест должен быть независимым исполняемым файлом 