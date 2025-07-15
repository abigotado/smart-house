#pragma once

#include "../../device/include/device.h"
#include "../../../shared/include/activatable.h"

namespace smart_house {

/**
 * @brief Умная лампочка с регулируемой яркостью
 */
class SmartLight : public Device, public IActivatable {
    public:
        using Device::Device;

        // Интерфейс IActivatable
        void turn_on() noexcept override;
        void turn_off() noexcept override;
        [[nodiscard]] IActivatable::PowerState get_power_state() const noexcept override;

        std::string to_string() const override;

        /// Устанавливает яркость (0-100)
        void set_brightness(int brightness);
        [[nodiscard]] int get_brightness() const noexcept;

        /// Создает копию устройства
        std::shared_ptr<Device> clone() const override;

    private:
        IActivatable::PowerState power_state_ = IActivatable::PowerState::OFF;
        int brightness_ = 100;
};

} // namespace smart_house