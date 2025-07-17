#pragma once

#include "../../device/include/device.h"
#include "../../../shared/include/measurable.h"
#include "../../../temperature_manager/include/temperature_manager.h"

namespace smart_house {

/**
 * @brief Термометр для измерения температуры
 */
class Thermometer : public Device, public IMeasurable {
    public:
        Thermometer(const std::string& name, TemperatureUnit unit = TemperatureUnit::CELSIUS);
        
        /// Конструктор копирования
        Thermometer(const Thermometer& other);
        
        Thermometer(Thermometer&& other) noexcept;
        Thermometer& operator=(Thermometer&& other) noexcept;
        
        // Интерфейс IMeasurable
        double read_value() const noexcept override;
        const std::string& get_unit() const noexcept override;
        bool get_is_calibrated() const noexcept override;
        void calibrate() override;
        
        std::string to_string() const override;
        
        /// Изменяет единицу измерения температуры (конвертирует текущее значение)
        void set_temperature_unit(TemperatureUnit unit) noexcept;

        /// Создает копию устройства
        std::shared_ptr<Device> clone() const override;

    private:
        /// Имитирует измерение температуры (устанавливает случайное значение)
        void simulate_measurement();
        
        double temperature_ = 0.0;
        bool is_calibrated_ = false;
        TemperatureManager temp_manager_;
};

} // namespace smart_house
 