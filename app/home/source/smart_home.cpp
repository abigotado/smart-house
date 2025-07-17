#include "smart_home.h"
#include "../../../shared/include/uuid.h"
#include <stdexcept>
#include <sstream>
 
namespace smart_house {
    SmartHome::SmartHome() : id_(generate_uuid()) {}

    Speaker& SmartHome::operator[](const std::string& name) {
        return speakers_.at(name);
    }

    const Speaker& SmartHome::operator[](const std::string& name) const {
        return speakers_.at(name);
    }

    const std::string& SmartHome::get_id() const noexcept {
        return id_;
    }

    bool SmartHome::add_speaker(const std::string& name, const Speaker::Room& room) {
        if (speakers_.find(name) != speakers_.end()) {
            return false;
        }
        speakers_.try_emplace(name, name, room);
        return true;
    }

    bool SmartHome::move_speaker(const std::string& name, const Speaker::Room& new_room) {
        if (speakers_.find(name) == speakers_.end()) {
            return false;
        }
        // speakers_[name].move_to_room(new_room);
        speakers_.at(name).move_to_room(new_room);
        return true;
    }

    bool SmartHome::rename_speaker(const std::string& old_name, const std::string& new_name) {
        // Проверяем, что старая колонка существует, а новой нет
        if (speakers_.find(old_name) == speakers_.end() || 
            speakers_.find(new_name) != speakers_.end() || 
            new_name.empty()) {
            return false;
        }
        
        // Извлекаем колонку из map и переименовываем
        auto node = speakers_.extract(old_name);
        node.mapped().rename(new_name);
        node.key() = new_name;
        speakers_.insert(std::move(node));
        return true;
    }

    bool SmartHome::remove_speaker(const std::string& name) {
        if (speakers_.find(name) == speakers_.end()) {
            return false;
        }
        speakers_.erase(name);
        return true;
    }

    std::size_t SmartHome::size() const noexcept {
        return speakers_.size();
    }

    const std::map<std::string, Speaker>& SmartHome::get_speakers() const noexcept {
        return speakers_;
    }

    std::string SmartHome::to_string() const {
        std::stringstream ss;
        ss << "SmartHome: " << id_ << std::endl;
        for (const auto& [name, speaker] : speakers_) {
            ss << "  " << speaker.to_string() << std::endl;
        }
        return ss.str();
    }
}