#pragma once

#include "../../device/include/device.h"
#include "../../../shared/include/activatable.h"
#include "../../../shared/include/measurable.h"
#include "../../../temperature_manager/include/temperature_manager.h"

namespace smart_house {

/**
 * @brief Умный чайник с контролем температуры
 */
class SmartKettle : public Device, public IActivatable, public IMeasurable {
    public:
        SmartKettle(const std::string& id, const std::string& name, TemperatureUnit unit = TemperatureUnit::CELSIUS)
            : Device(id, name), temp_manager(unit) {};
        
        // Интерфейс IActivatable
        void turn_on() noexcept override;
        void turn_off() noexcept override;
        IActivatable::PowerState get_power_state() const noexcept override;
        
        // Интерфейс IMeasurable
        [[nodiscard]] double read_value() const noexcept override;
        [[nodiscard]] const std::string& get_unit() const noexcept override;
        [[nodiscard]] bool get_is_calibrated() const noexcept override;
        void calibrate() override;
        
        std::shared_ptr<Device> clone() const override;
        std::string to_string() const override;
        
        /// Устанавливает целевую температуру нагрева
        void set_target_temperature(double temperature);
        
        /// Изменяет единицу измерения температуры
        void set_temperature_unit(TemperatureUnit unit) noexcept;

    private:
        IActivatable::PowerState power_state_ = IActivatable::PowerState::OFF;
        double temperature_ = 20.0;
        bool calibrated_ = true;
        double target_temp_ = 100.0;
        TemperatureManager temp_manager_;
};

} 