#pragma once

#include "../../../shared/include/object.h"
#include "../../devices/device/include/device.h"
#include "../../../shared/include/activatable.h"
#include <map>
#include <memory>
#include <string>
#include <atomic>

namespace smart_house {

/**
 * @brief Умная колонка - управляет устройствами в определенной комнате
 */
class Speaker : public Object {
public:
    /**
     * @brief Типы комнат
     */
        enum class RoomType {
            LIVING_ROOM, CORRIDOR, RESTROOM, KITCHEN, BALCONY
        };

    /**
     * @brief Структура с данными комнаты
     */
    struct Room : public Object {
        std::string name;
        int room_number;
        RoomType room_type;

        Room(const std::string& name, int room_number, RoomType type)
            : name(name), room_number(room_number), room_type(type) {}

        std::string to_string() const override {
            return name + " (" + std::to_string(room_number) + ", " + Speaker::room_type_to_string(room_type) + ")";
        }
    };

        /// Преобразует тип комнаты в строку
        static std::string room_type_to_string(RoomType type);

    /// Конструктор с готовой структурой Room
    Speaker(const std::string& speaker_name, const Room& room);

    /// Запрещаем копирование
    Speaker(const Speaker&) = delete;
    Speaker& operator=(const Speaker&) = delete;
    
    /// Получает имя колонки (для сортировки)
    [[nodiscard]] const std::string& get_name() const noexcept;

    /// Добавляет устройство (false если ID уже существует)
    bool add_device(std::shared_ptr<Device> device);
    
    /// Удаляет устройство по ID (false если не найдено)
    bool remove_device(const std::string& device_id);
    
    [[nodiscard]] std::shared_ptr<Device> get_device(const std::string& device_id);
    [[nodiscard]] std::shared_ptr<const Device> get_device(const std::string& device_id) const;
    [[nodiscard]] const std::map<std::string, std::shared_ptr<Device>>& get_all_devices() const noexcept;

    /// Обходит устройства и включает выключенные
    void check_and_activate_devices();

    [[nodiscard]] RoomType get_room_type() const noexcept;
    [[nodiscard]] std::size_t get_device_count() const noexcept;
    [[nodiscard]] const Room& get_room() const noexcept;
    
    /// Перемещает колонку в другую комнату
    void move_to_room(const Room& new_room);
    
    [[nodiscard]] std::string to_string() const override;

    /// Разрешаем SmartHome доступ к приватным полям
    friend class SmartHome;

private:
    /// Перемещение (фактически доступно только для SmartHome)
    Speaker(Speaker&&) = default;
    Speaker& operator=(Speaker&&) = default;
    
    /// Переименовывает колонку
    bool rename(const std::string& new_name);
    
    std::string name_;
    std::map<std::string, std::shared_ptr<Device>> devices_;
    Room room_;
};

} // namespace smart_house 