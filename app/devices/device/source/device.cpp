#include "device.h"
#include "../../../shared/include/uuid.h"

namespace smart_house {

Device::Device(const std::string& name)
    : id_(generate_uuid()), name_(name), status_(DeviceStatus::OFFLINE) {
}

Device::Device(const Device& other)
    : id_(generate_uuid()), // Новый UUID при копировании
      name_(other.name_), 
      status_(other.status_) {
}

Device::Device(Device&& other) noexcept
    : id_(generate_uuid()), // Новый UUID при перемещении
      name_(std::move(other.name_)), 
      status_(other.status_) {
    other.status_ = DeviceStatus::OFFLINE; // Сбрасываем статус исходного объекта
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

Device& Device::operator=(Device&& other) noexcept {
    if (this != &other) {
        id_ = generate_uuid(); // Новый UUID при перемещении
        name_ = std::move(other.name_);
        status_ = other.status_;
        other.status_ = DeviceStatus::OFFLINE; // Сбрасываем статус исходного объекта
    }
    return *this;
}

} // namespace smart_house 