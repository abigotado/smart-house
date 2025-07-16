#pragma once

namespace smart_house {

class IActivatable {
    public:
        enum class PowerState { ON, OFF };

        virtual ~IActivatable() = default;

        virtual void turn_on() = 0;
        virtual void turn_off() = 0;
        [[nodiscard]] virtual PowerState get_power_state() const noexcept = 0;
    };
}