#pragma once

namespace smart_house {

class IActivatable {
    public:
        enum class PowerState { ON, OFF };

        virtual ~IActivatable() = default;

        virtual void turn_on() noexcept = 0;
        virtual void turn_off() noexcept = 0;
        [[nodiscard]] virtual PowerState get_power_state() const noexcept = 0;
    };
}