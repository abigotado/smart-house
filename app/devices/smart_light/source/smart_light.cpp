// Умная лампа - будет реализована позже
#include "smart_light.h"
#include <sstream>
 
namespace smart_house {

    SmartLight::SmartLight(const SmartLight& other)
        : Device(other.get_name()),
          power_state_(other.power_state_),
          brightness_(other.brightness_) {}

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

    void SmartLight::turn_on() noexcept {
        power_state_ = IActivatable::PowerState::ON;
    }

    void SmartLight::turn_off() noexcept {
        power_state_ = IActivatable::PowerState::OFF;
    }

    IActivatable::PowerState SmartLight::get_power_state() const noexcept {
        return power_state_;
    }

    void SmartLight::set_brightness(int brightness) {
        if (brightness >= 0 && brightness <= 100) {
            brightness_ = brightness;
        }
    }

    int SmartLight::get_brightness() const noexcept {
        return brightness_;
    }

    std::shared_ptr<Device> SmartLight::clone() const {
        return std::make_shared<SmartLight>(*this);
    }

    std::string SmartLight::to_string() const {
        std::stringstream ss;
        ss << "SmartLight: " << get_name() << " (ID: " << get_id() << ")";
        ss << " - Status: " << (get_status() == Device::DeviceStatus::ONLINE ? "ONLINE" : "OFFLINE");
        ss << ", Power: " << (power_state_ == IActivatable::PowerState::ON ? "ON" : "OFF");
        ss << ", Brightness: " << brightness_ << "%";
        return ss.str();
    }

} // namespace smart_house 