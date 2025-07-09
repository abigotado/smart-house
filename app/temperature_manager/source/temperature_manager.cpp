#include "temperature_manager.h"

namespace smart_house {

// Конструктор
TemperatureManager::TemperatureManager(TemperatureUnit unit) : temperature_unit_(unit) {
}

// Сеттер для единицы измерения
void TemperatureManager::set_unit(TemperatureUnit unit) noexcept {
    temperature_unit_ = unit;
}

// Геттер для единицы измерения
TemperatureUnit TemperatureManager::get_unit() const noexcept {
    return temperature_unit_;
}

// Получение строкового представления текущей единицы
std::string TemperatureManager::get_unit_string() const {
    return unit_to_string(temperature_unit_);
}

// Конвертация в текущую единицу измерения
double TemperatureManager::convert_to_unit(double value, TemperatureUnit from) const {
    return convert(value, from, temperature_unit_);
}

// Статический метод - преобразование enum в строку
std::string TemperatureManager::unit_to_string(TemperatureUnit unit) {
    switch (unit) {
        case TemperatureUnit::CELSIUS:
            return "°C";
        case TemperatureUnit::FAHRENHEIT:
            return "°F";
        case TemperatureUnit::KELVIN:
            return "K";
        default:
            return "°C";
    }
}

// Статический метод - конвертация температуры
double TemperatureManager::convert(double value, TemperatureUnit from, TemperatureUnit to) {
    if (from == to) return value;
    
    // Сначала конвертируем в Цельсий
    double celsius = value;
    if (from == TemperatureUnit::FAHRENHEIT) {
        celsius = (value - 32.0) * 5.0 / 9.0;
    } else if (from == TemperatureUnit::KELVIN) {
        celsius = value - 273.15;
    }
    
    // Затем из Цельсия в целевую единицу
    switch (to) {
        case TemperatureUnit::CELSIUS:
            return celsius;
        case TemperatureUnit::FAHRENHEIT:
            return celsius * 9.0 / 5.0 + 32.0;
        case TemperatureUnit::KELVIN:
            return celsius + 273.15;
        default:
            return celsius;
    }
}

} 