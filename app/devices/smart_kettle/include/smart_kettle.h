#pragma once

#include "../../device/include/device.h"
#include "../../interfaces/include/activatable.h"
#include "../../interfaces/include/measurable.h"
#include "../../../temperature_manager/include/temperature_manager.h"

namespace smart_house {
    class SmartKettle : public Device, public IActivatable, public IMeasurable {
        public:
            SmartKettle(const std::string& id, const std::string& name, TemperatureUnit unit = TemperatureUnit::CELSIUS)
                : Device(id, name), temp_manager(unit) {};
            
            void turn_on() noexcept override;
            void turn_off() noexcept override;
            IActivatable::PowerState get_power_state() const noexcept override;
            
            double read_value() const noexcept override;
            const std::string& get_unit() const noexcept override;
            bool get_is_calibrated() const noexcept override;
            void calibrate() override;
            
            std::shared_ptr<Device> clone() const override;
            std::string to_string() const override;
            
            // SmartKettle specific methods
            void set_target_temperature(double temperature);
            
            // Методы для работы с единицами измерения через композицию
            void set_temperature_unit(TemperatureUnit unit) noexcept;

        private:
            IActivatable::PowerState power_state = IActivatable::PowerState::OFF;
            double temperature = 20.0;
            bool calibrated = true;
            double target_temp = 100.0;
            TemperatureManager temp_manager;  // Композиция для управления температурными единицами
    };
} 