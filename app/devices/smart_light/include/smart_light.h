#pragma once

#include "../../device/include/device.h"
#include "../../interfaces/include/activatable.h"

namespace smart_house {
    class SmartLight : public Device, public IActivatable {
        public:
            using Device::Device;
            void turn_on() noexcept override;
            void turn_off() noexcept override;
            [[nodiscard]] IActivatable::PowerState get_power_state() const noexcept override;
            std::shared_ptr<Device> clone() const override;
            std::string to_string() const override;
            [[nodiscard]] int get_brightness() const noexcept;

            void set_brightness(int brightness);

        private:
            IActivatable::PowerState power_state = IActivatable::PowerState::OFF;
            int brightness = 100;
    };
} 