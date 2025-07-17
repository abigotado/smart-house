// Умная лампа - будет реализована позже
#include "smart_light.h"
 
// Временная заглушка для компиляции
namespace smart_house {
    // Реализация будет добавлена позже

    SmartLight::SmartLight(SmartLight&& other) noexcept
        : Device(std::move(other)),
          power_state_(other.power_state_),
          brightness_(other.brightness_) {}

    SmartLight& SmartLight::operator=(SmartLight&& other) noexcept {
        if (this != &other) {
            Device::operator=(std::move(other));
            power_state_ = other.power_state_;
            brightness_ = other.brightness_;
        }
        return *this;
    }
} 