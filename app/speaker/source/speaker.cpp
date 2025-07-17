#include "speaker.h"
 
namespace smart_house {
    Speaker::Speaker(const std::string& speaker_name, const Room& room) : name_(speaker_name), room_(room) {}

    const std::string& Speaker::get_name() const noexcept {
        return name_;
    }

    bool Speaker::add_device(std::shared_ptr<Device> device) {
        std::string device_id = device->get_id();
        if (devices_.find(device_id) != devices_.end()) {
            return false;
        }
        devices_[device_id] = device;
        return true;
    }

    bool Speaker::remove_device(const std::string& device_id) {
        if (devices_.find(device_id) == devices_.end()) {
            return false;
        }
        devices_.erase(device_id);
        return true;
    }

    std::shared_ptr<Device> Speaker::get_device(const std::string& device_id) {
        if (devices_.find(device_id) == devices_.end()) {
            return nullptr;
        }
        return devices_.at(device_id);
    }

    std::shared_ptr<const Device> Speaker::get_device(const std::string& device_id) const {
        if (devices_.find(device_id) == devices_.end()) {
            return nullptr;
        }
        return devices_.at(device_id);
    }

    const std::map<std::string, std::shared_ptr<Device>>& Speaker::get_all_devices() const noexcept {
        return devices_;
    }

    Speaker::RoomType Speaker::get_room_type() const noexcept {
        return room_.room_type;
    }

    std::size_t Speaker::get_device_count() const noexcept {
        return devices_.size();
    }

    const Speaker::Room& Speaker::get_room() const noexcept {
        return room_;
    }

    void Speaker::move_to_room(const Room& new_room) {
        room_ = new_room;
    }

    bool Speaker::rename(const std::string& new_name) {
        if (new_name.empty()) {
            return false;
        }
        name_ = new_name;
        return true;
    }

    void Speaker::check_and_activate_devices() {
        for (const auto& [id, device] : devices_) {
            auto activatable = std::dynamic_pointer_cast<IActivatable>(device);
            if (activatable && activatable->get_power_state() == IActivatable::PowerState::OFF) {
                activatable->turn_on();
            }
        }
    }

    std::string Speaker::room_type_to_string(RoomType type) {
        switch (type) {
            case RoomType::LIVING_ROOM: return "Living Room";
            case RoomType::CORRIDOR: return "Corridor";
            case RoomType::RESTROOM: return "Restroom";
            case RoomType::KITCHEN: return "Kitchen";
            case RoomType::BALCONY: return "Balcony";
            default: return "Unknown";
        }
    }

    std::string Speaker::to_string() const {
        std::stringstream ss;
        ss << "Speaker: " << name_ << " in room " << room_.name << " (" << room_.room_number << ")" << std::endl;
        for (const auto& [device_id, device] : devices_) {
            ss << "  " << device->to_string() << std::endl;
        }
        return ss.str();
    }
} 