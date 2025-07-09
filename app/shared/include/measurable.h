#pragma once

#include <string>

namespace smart_house {

class IMeasurable {
    public:
        virtual ~IMeasurable() = default;

        [[nodiscard]] virtual double read_value() const = 0;
        [[nodiscard]] virtual const std::string& get_unit() const noexcept = 0;
        [[nodiscard]] virtual bool get_is_calibrated() const noexcept = 0;
        virtual void calibrate() = 0;
    };
}