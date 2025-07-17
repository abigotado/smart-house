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
│   ├── devices/                  # Все что связано с устройствами
│   │   ├── device/               # Абстрактный базовый класс Device
│   │   ├── vacuum_cleaner/       # Пылесос
│   │   ├── smart_light/          # Умная лампа
│   │   ├── thermometer/          # Термометр (использует TemperatureManager)
│   │   └── smart_kettle/         # Умный чайник (использует TemperatureManager)
│   ├── shared/                   # Общие интерфейсы (IActivatable, IMeasurable, Object)
│   ├── speaker/                  # Класс Speaker с вложенным Room
│   └── home/                     # Класс SmartHome
├── tests/                        # Модульные тесты
├── docs/                         # Документация и UML
├── examples/                     # Примеры использования
└── CMakeLists.txt                # Конфигурация сборки
```

## Сборка

```bash
mkdir build && cd build
cmake ..
make
```

## Запуск

```bash
# Пример демонстрации
./examples/SmartHouseDemo/SmartHouseDemo

# Тесты (каждый бинарник отдельно)
./tests/unit_tests/test_device
./tests/unit_tests/test_smart_home
./tests/unit_tests/test_speaker
./tests/unit_tests/test_temperature_manager
./tests/unit_tests/test_smart_light
./tests/unit_tests/test_thermometer
./tests/unit_tests/devices/test_smart_kettle
./tests/unit_tests/devices/test_vacuum_cleaner
```

## Пример использования

```cpp
#include "app/home/include/smart_home.h"
#include "app/devices/smart_kettle/include/smart_kettle.h"
#include "app/devices/thermometer/include/thermometer.h"
#include "app/temperature_manager/include/temperature_manager.h"

int main() {
    using namespace smart_house;
    
    SmartHome home;
    home.add_speaker("kitchen", Speaker::Room("Kitchen", 1, Speaker::Room::RoomType::KITCHEN));
    
    auto kettle = std::make_shared<SmartKettle>("kettle_01", TemperatureUnit::CELSIUS);
    auto thermometer = std::make_shared<Thermometer>("thermo_01", TemperatureUnit::FAHRENHEIT);
    
    home["kitchen"].add_device(kettle);
    home["kitchen"].add_device(thermometer);
    
    kettle->set_temperature_unit(TemperatureUnit::FAHRENHEIT);
    thermometer->set_temperature_unit(TemperatureUnit::CELSIUS);
    
    double fahrenheit = TemperatureManager::convert(100.0, 
        TemperatureUnit::CELSIUS, TemperatureUnit::FAHRENHEIT);
    std::cout << "100°C = " << fahrenheit << "°F" << std::endl;
    
    // Активация всех устройств в колонке
    home["kitchen"].check_and_activate_devices();
    
    std::cout << home << std::endl;
    return 0;
}
```

## Диаграмма классов

См. `docs/SmartHouse_ClassDiagram.png` или `docs/smart_house_uml.puml`
