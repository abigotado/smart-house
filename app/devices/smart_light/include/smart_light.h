#pragma once

#include "../../device/include/device.h"
#include "../../../shared/include/activatable.h"

namespace smart_house {
    class SmartLight : public Device, public IActivatable {
        public:
            using Device::Device;

            // Интерфейс IActivatable
            void turn_on() noexcept override;
            void turn_off() noexcept override;
            [[nodiscard]] IActivatable::PowerState get_power_state() const noexcept override;

            // Виртуальные методы из Device
            std::shared_ptr<Device> clone() const override;
            std::string to_string() const override;

            // Собственные методы SmartLight
            void set_brightness(int brightness);
            [[nodiscard]] int get_brightness() const noexcept;

        private:
            IActivatable::PowerState power_state = IActivatable::PowerState::OFF;
            int brightness = 100;
    };
}