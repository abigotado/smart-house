#pragma once

#include "../../device/include/device.h"
#include "../../../shared/include/activatable.h"

namespace smart_house {

/**
 * @brief Робот-пылесос с аккумулятором
 */
class VacuumCleaner : public Device, public IActivatable {
    public:
        using Device::Device;

        // Интерфейс IActivatable
        void turn_on() noexcept override;
        void turn_off() noexcept override;
        [[nodiscard]] IActivatable::PowerState get_power_state() const noexcept override;
        
        std::string to_string() const override;
        
        [[nodiscard]] int get_battery_level() const noexcept;

    private:
        IActivatable::PowerState power_state_ = IActivatable::PowerState::OFF;
        int battery_level_ = 100;
};

} // namespace smart_house 