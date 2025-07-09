#pragma once

#include "enum/temperature_unit.h"
#include <string>

namespace smart_house {

class TemperatureManager {
    public:
        explicit TemperatureManager(TemperatureUnit unit = TemperatureUnit::CELSIUS);
        
        // Методы для работы с единицами измерения
        void set_unit(TemperatureUnit unit) noexcept;
        TemperatureUnit get_unit() const noexcept;
        
        // Утилитарные методы
        std::string get_unit_string() const;
        double convert_to_unit(double value, TemperatureUnit from) const;
        
        // Статические утилитарные методы
        static std::string unit_to_string(TemperatureUnit unit);
        static double convert(double value, TemperatureUnit from, TemperatureUnit to);

    private:
        TemperatureUnit temperature_unit_;
};

} 