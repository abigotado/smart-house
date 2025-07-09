#pragma once

#include "enum/temperature_unit.h"
#include <string>

namespace smart_house {

/**
 * @brief Управляет единицами измерения температуры и конвертацией
 */
class TemperatureManager {
    public:
        explicit TemperatureManager(TemperatureUnit unit = TemperatureUnit::CELSIUS);
        
        void set_unit(TemperatureUnit unit) noexcept;
        TemperatureUnit get_unit() const noexcept;
        
        /// Получает строковое представление текущей единицы
        std::string get_unit_string() const;
        
        /// Конвертирует значение из указанной единицы в текущую
        double convert_to_unit(double value, TemperatureUnit from) const;
        
        /// Преобразует единицу измерения в строку
        static std::string unit_to_string(TemperatureUnit unit);
        
        /// Конвертирует значение между единицами измерения
        static double convert(double value, TemperatureUnit from, TemperatureUnit to);

    private:
        TemperatureUnit temperature_unit_;
};

} 