#pragma once

#include "../../device/include/device.h"
#include "../../../shared/include/activatable.h"

namespace smart_house {
    class VacuumCleaner : public Device, public IActivatable {
        public:
            using Device::Device;

            void turn_on() noexcept override;
            void turn_off() noexcept override;
            [[nodiscard]] IActivatable::PowerState get_power_state() const noexcept override;
            std::shared_ptr<Device> clone() const override;
            std::string to_string() const override;
            
            [[nodiscard]] int get_battery_level() const noexcept;

        private:
            IActivatable::PowerState power_state = IActivatable::PowerState::OFF;
            int battery_level = 100;
    };
} 