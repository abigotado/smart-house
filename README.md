# Smart House Management System

Система управления умным домом на C++17 с использованием современных принципов ООП.

## Требования

- C++17 или выше
- CMake 3.15+
- Компилятор: GCC 7+, Clang 5+, MSVC 2017+

## Структура проекта

```
smart-house/
├── include/smart_house/          # Заголовочные файлы
│   ├── device/                   # Интерфейсы и базовые классы
│   ├── home/                     # Класс SmartHome
│   ├── room/                     # Enums и типы комнат
│   └── speaker/                  # Класс Speaker
├── src/                          # Реализация
├── tests/                        # Модульные тесты
├── docs/                         # Документация и UML
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
./smart_house_demo

# Тесты
./tests/smart_house_tests
```

## Тестирование памяти

```bash
# Проверка утечек памяти (Linux/macOS)
valgrind --leak-check=full ./smart_house_demo
valgrind --leak-check=full ./tests/smart_house_tests
```

## Основные компоненты

- **IDevice** - базовый интерфейс для всех устройств
- **IActiveDevice** - интерфейс для активных устройств (включение/выключение)
- **ISensorDevice** - интерфейс для сенсорных устройств (чтение данных)
- **Device** - абстрактный базовый класс
- **Speaker** - управление устройствами в комнате (с вложенным классом Room)
- **SmartHome** - главный класс системы

## Пример использования

```cpp
#include "smart_house/SmartHome.h"
#include "smart_house/devices/SmartKettle.h"

int main() {
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
