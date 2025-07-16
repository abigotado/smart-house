#include "device.h"
#include <random>
#include <sstream>
#include <iomanip>

namespace smart_house {

std::string generate_device_uuid() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    
    std::stringstream ss;
    ss << "device_";
    for (int i = 0; i < 8; ++i) {
        ss << std::hex << dis(gen);
    }
    return ss.str();
}

Device::Device(const std::string& name)
    : id_(generate_device_uuid()), name_(name), status_(DeviceStatus::OFFLINE) {
}

Device::Device(const Device& other)
    : id_(generate_device_uuid()), // Новый UUID при копировании
      name_(other.name_), 
      status_(other.status_) {
}

const std::string& Device::get_id() const noexcept {
    return id_;
}

const std::string& Device::get_name() const noexcept {
    return name_;
}

Device::DeviceStatus Device::get_status() const noexcept {
    return status_;
}

void Device::set_status(DeviceStatus status) noexcept {
    status_ = status;
}

} // namespace smart_house 