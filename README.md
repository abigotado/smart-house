# Smart House Management System

Система управления умным домом на C++20 с использованием современных принципов ООП.

## Требования

- C++20 или выше
- CMake 3.20+
- Компилятор: GCC 10+, Clang 10+, MSVC 2019+

## Структура проекта

```log
smart-house/
├── app/                          # Основное приложение
│   ├── temperature_manager/      # Утилиты для работы с температурой
│   │   ├── include/              # Заголовочные файлы
│   │   │   ├── temperature_manager.h
│   │   │   └── enum/
│   │   │       └── temperature_unit.h
│   │   └── source/               # Исходные файлы
│   │       └── temperature_manager.cpp
│   ├── devices/                  # Все что связано с устройствами
│   │   ├── device/               # Абстрактный базовый класс Device
│   │   │   ├── include/          # Заголовочные файлы
│   │   │   └── source/           # Исходные файлы
│   │   ├── interfaces/           # Интерфейсы IActivatable, IMeasurable
│   │   │   └── include/          # Заголовочные файлы
│   │   ├── vacuum_cleaner/       # Пылесос
│   │   │   ├── include/          # Заголовочные файлы
│   │   │   └── source/           # Исходные файлы
│   │   ├── smart_light/          # Умная лампа
│   │   │   ├── include/          # Заголовочные файлы
│   │   │   └── source/           # Исходные файлы
│   │   ├── thermometer/          # Термометр (использует TemperatureManager)
│   │   │   ├── include/          # Заголовочные файлы
│   │   │   └── source/           # Исходные файлы
│   │   └── smart_kettle/         # Умный чайник (использует TemperatureManager)
│   │       ├── include/          # Заголовочные файлы
│   │       └── source/           # Исходные файлы
│   ├── speaker/                  # Класс Speaker с вложенным Room
│   │   ├── include/              # Заголовочные файлы
│   │   └── source/               # Исходные файлы
│   └── home/                     # Класс SmartHome
│       ├── include/              # Заголовочные файлы
│       └── source/               # Исходные файлы
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

### Утилиты

- **TemperatureManager** - управление единицами измерения температуры (композиция)
- **TemperatureUnit** - enum для единиц измерения (Celsius, Fahrenheit, Kelvin)

### Базовые классы и интерфейсы

- **Device** - абстрактный базовый класс для всех устройств
- **IActivatable** - интерфейс для активных устройств (включение/выключение)
- **IMeasurable** - интерфейс для измерительных устройств (чтение данных)

### Устройства

- **VacuumCleaner** - пылесос (активное устройство)
- **SmartLight** - умная лампа (активное устройство с управлением яркостью)
- **Thermometer** - термометр (измерительное устройство + TemperatureManager)
- **SmartKettle** - умный чайник (активное + измерительное устройство + TemperatureManager)

### Управление

- **Speaker** - управление устройствами в комнате (с вложенным классом Room)
- **SmartHome** - главный класс системы

## Пример использования

```cpp
#include "app/home/include/smart_home.h"
#include "app/devices/smart_kettle/include/smart_kettle.h"
#include "app/devices/thermometer/include/thermometer.h"
#include "app/temperature_manager/include/temperature_manager.h"

int main() {
    using namespace smart_house;
    
    SmartHome home;
    
    // Добавление комнаты
    home.addSpeaker("kitchen", Speaker::Room::RoomType::KITCHEN);
    
    // Добавление устройств с разными единицами измерения
    auto kettle = std::make_shared<SmartKettle>("kettle_01", "Smart Kettle", 
                                               TemperatureUnit::CELSIUS);
    auto thermometer = std::make_shared<Thermometer>("thermo_01", "Kitchen Thermometer", 
                                                    TemperatureUnit::FAHRENHEIT);
    
    home["kitchen"].addDevice(kettle);
    home["kitchen"].addDevice(thermometer);
    
    // Работа с температурными единицами
    kettle->set_temperature_unit(TemperatureUnit::FAHRENHEIT);
    thermometer->set_temperature_unit(TemperatureUnit::CELSIUS);
    
    // Статическое использование утилит
    double fahrenheit = TemperatureManager::convert(100.0, 
        TemperatureUnit::CELSIUS, TemperatureUnit::FAHRENHEIT);
    std::cout << "100°C = " << fahrenheit << "°F" << std::endl;
    
    // Активация всех устройств
    home.activateAllSpeakers();
    
    // Вывод информации
    std::cout << home << std::endl;
    
    return 0;
}
```

## Диаграмма классов

См. `docs/SmartHouse_ClassDiagram.png` или `docs/smart_house_uml.puml`
