// Термометр - будет реализован позже
#include "thermometer.h"
 
// Временная заглушка для компиляции
namespace smart_house {
    // Реализация будет добавлена позже

    Thermometer::Thermometer(Thermometer&& other) noexcept
        : Device(std::move(other)),
          temperature_(other.temperature_),
          is_calibrated_(other.is_calibrated_),
          temp_manager_(std::move(other.temp_manager_)) {}

    Thermometer& Thermometer::operator=(Thermometer&& other) noexcept {
        if (this != &other) {
            Device::operator=(std::move(other));
            temperature_ = other.temperature_;
            is_calibrated_ = other.is_calibrated_;
            temp_manager_ = std::move(other.temp_manager_);
        }
        return *this;
    }
} 