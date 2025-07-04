# 🏠 Smart House - Библиотека управления умным домом

Библиотека для управления умным домом на C++. Система включает управление умными колонками, устройствами различных типов и комнатами.

## 🏗️ Архитектура системы

```mermaid
classDiagram
    class RoomType {
        <<enumeration>>
        LIVING_ROOM
        BEDROOM
        CORRIDOR
        RESTROOM
        KITCHEN
        BALCONY
    }
    
    class DeviceStatus {
        <<enumeration>>
        ONLINE
        OFFLINE
    }
    
    class RoomDescriptor {
        -string roomName
        -int roomNumber
        -RoomType roomType
        +RoomDescriptor(string name, int number, RoomType type)
        +string getName() const
        +int getNumber() const
        +RoomType getType() const
    }
    
    class SmartDevice {
        <<abstract>>
        #int deviceId
        #string deviceName
        #DeviceStatus status
        +SmartDevice(int id, string name)
        +virtual ~SmartDevice()
        +int getId() const
        +string getName() const
        +DeviceStatus getStatus() const
        +virtual void turnOn() = 0
        +virtual void turnOff() = 0
        +virtual string getInfo() const = 0
    }
    
    class IActiveDevice {
        <<interface>>
        +virtual ~IActiveDevice() = 0
        +virtual void activate() = 0
        +virtual void deactivate() = 0
        +virtual bool getActivationStatus() const = 0
        +virtual string getMainFunction() const = 0
    }
    
    class ISensorDevice {
        <<interface>>
        +virtual ~ISensorDevice() = 0
        +virtual double getValue() const = 0
        +virtual string getUnit() const = 0
        +virtual void updateValue(double value) = 0
    }
    
    class ActiveDevice {
        -bool isActivated
        -string mainFunction
        +ActiveDevice(int id, string name, string function)
        +void activate()
        +void deactivate()
        +bool getActivationStatus() const
        +string getMainFunction() const
        +void turnOn() override
        +void turnOff() override
        +string getInfo() const override
    }
    
    class SensorDevice {
        -double sensorValue
        -string measurementUnit
        +SensorDevice(int id, string name, string unit)
        +double getValue() const
        +string getUnit() const
        +void updateValue(double value)
        +void turnOn() override
        +void turnOff() override
        +string getInfo() const override
    }
    
    class HybridDevice {
        -bool isActivated
        -string mainFunction
        -double sensorValue
        -string measurementUnit
        +HybridDevice(int id, string name, string function, string unit)
        +void activate()
        +void deactivate()
        +bool getActivationStatus() const
        +string getMainFunction() const
        +double getValue() const
        +string getUnit() const
        +void updateValue(double value)
        +void turnOn() override
        +void turnOff() override
        +string getInfo() const override
    }
    
    class SmartSpeaker {
        -RoomDescriptor roomDesc
        -vector~shared_ptr~SmartDevice~~ devices
        +SmartSpeaker(string roomName, int roomNumber, RoomType roomType)
        +void addDevice(shared_ptr~SmartDevice~ device)
        +void removeDevice(int deviceId)
        +void checkAndUpdateDevices()
        +string getRoomName() const
        +int getDeviceCount() const
    }
    
    class SmartHome {
        -map~string, shared_ptr~SmartSpeaker~~ speakers
        +SmartHome()
        +void addSpeaker(shared_ptr~SmartSpeaker~ speaker)
        +void removeSpeaker(string roomName)
        +shared_ptr~SmartSpeaker~ operator[](const string& roomName)
        +void manageAllDevices()
        +int getTotalDeviceCount() const
    }
    
    RoomDescriptor --> RoomType : uses
    SmartDevice --> DeviceStatus : uses
    SmartDevice <|-- ActiveDevice : inherits
    SmartDevice <|-- SensorDevice : inherits
    SmartDevice <|-- HybridDevice : inherits
    IActiveDevice <|.. ActiveDevice : implements
    ISensorDevice <|.. SensorDevice : implements
    IActiveDevice <|.. HybridDevice : implements
    ISensorDevice <|.. HybridDevice : implements
    SmartSpeaker *-- RoomDescriptor : contains
    SmartSpeaker o-- SmartDevice : aggregates
    SmartHome o-- SmartSpeaker : aggregates
```

## 📱 Основные компоненты

### Типы устройств

- **Активные устройства** - имеют основную функцию (пылесос, лампочка)
- **Устройства-датчики** - снимают показания (термометр, датчик протечки)
- **Гибридные устройства** - совмещают функции (чайник, увлажнитель)

### Управление

- **SmartHome** - главный класс системы с коллекцией колонок
- **SmartSpeaker** - умная колонка для управления устройствами в комнате
- **RoomDescriptor** - описание комнаты (имя, номер, тип)

### Особенности

- Автоматическая сортировка колонок по имени комнаты (std::map)
- Перегрузка операторов `<<` и `[]` для удобного доступа
- Автоматическое включение выключенных устройств
- Интерфейсный подход для гибридных устройств (избегает diamond problem)

## 📂 Структура проекта

```log
smart-house/
├── docs/                          # Документация и диаграммы
├── include/smart_house/           # Заголовочные файлы
├── src/                          # Исходный код
├── examples/                     # Примеры использования
└── CMakeLists.txt               # Конфигурация сборки
```

## 💡 Пример использования

```cpp
#include "smart_house/SmartHome.h"
#include "smart_house/SmartSpeaker.h"
#include "smart_house/devices/ActiveDevice.h"

int main() {
    // Создаем умный дом
    SmartHome home;
    
    // Добавляем колонку в спальню
    auto speaker = std::make_shared<SmartSpeaker>("Спальня", 1, RoomType::BEDROOM);
    home.addSpeaker(speaker);
    
    // Добавляем устройства
    auto lamp = std::make_shared<ActiveDevice>(1, "Умная лампа", "освещение");
    speaker->addDevice(lamp);
    
    // Управляем устройствами
    home.manageAllDevices();
    
    // Вывод информации о доме
    std::cout << home << std::endl;
    
    return 0;
}
```
