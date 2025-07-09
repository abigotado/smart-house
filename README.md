# Smart House Management System

Система управления умным домом на C++20 с использованием современных принципов ООП.

## Требования

- C++20 или выше
- CMake 3.20+
- Компилятор: GCC 10+, Clang 10+, MSVC 2019+

## Структура проекта

```
smart-house/
├── app/                          # Основное приложение
│   ├── device/                   # Абстрактный базовый класс Device
│   ├── interfaces/               # Интерфейсы IActivatable, IMeasurable
│   ├── devices/                  # Конкретные устройства
│   │   ├── vacuum_cleaner/       # Пылесос
│   │   ├── smart_light/          # Умная лампа
│   │   ├── thermometer/          # Термометр
│   │   └── smart_kettle/         # Умный чайник
│   ├── speaker/                  # Класс Speaker с вложенным Room
│   └── home/                     # Класс SmartHome
├── tests/                        # Модульные тесты
├── docs/                         # Документация и UML
├── examples/                     # Примеры использования
└── CMakeLists.txt               # Конфигурация сборки
```

## Сборка

```bash
mkdir build && cd build
cmake ..
make
```

## Запуск

```bash
# Основная программа
./app/smart_house_demo

# Тесты
./tests/smart_house_tests
```

## Тестирование памяти

```bash
# Проверка утечек памяти (Linux/macOS)
valgrind --leak-check=full ./app/smart_house_demo
valgrind --leak-check=full ./tests/smart_house_tests
```

## Основные компоненты

- **Device** - абстрактный базовый класс для всех устройств
- **IActivatable** - интерфейс для активных устройств (включение/выключение)
- **IMeasurable** - интерфейс для измерительных устройств (чтение данных)
- **VacuumCleaner** - пылесос (активное устройство)
- **SmartLight** - умная лампа (активное устройство)
- **Thermometer** - термометр (измерительное устройство)
- **SmartKettle** - умный чайник (активное + измерительное устройство)
- **Speaker** - управление устройствами в комнате (с вложенным классом Room)
- **SmartHome** - главный класс системы

## Пример использования

```cpp
#include "app/home/include/smart_home.h"
#include "app/devices/smart_kettle/include/smart_kettle.h"

int main() {
    using namespace smart_house;
    
    SmartHome home;
    
    // Добавление комнаты
    home.addSpeaker("kitchen", Speaker::Room::RoomType::KITCHEN);
    
    // Добавление устройства
    auto kettle = std::make_shared<SmartKettle>("kettle_01", "Smart Kettle");
    home["kitchen"].addDevice(kettle);
    
    // Активация всех устройств
    home.activateAllSpeakers();
    
    // Вывод информации
    std::cout << home << std::endl;
    
    return 0;
}
```

## Диаграмма классов

См. `docs/SmartHouse_ClassDiagram.png` или `docs/smart_house_uml.puml`
