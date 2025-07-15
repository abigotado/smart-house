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
     * @brief Комната, где расположена колонка
     */
    class Room : public Object {
    public:
        enum class RoomType {
            LIVING_ROOM, CORRIDOR, RESTROOM, KITCHEN, BALCONY
        };

        /// Создает комнату с указанными параметрами
        Room(const std::string& name, int room_number, RoomType type);
        
        // Запрещаем копирование, разрешаем перемещение
        Room(const Room&) = delete;
        Room& operator=(const Room&) = delete;
        Room(Room&&) = default;
        Room& operator=(Room&&) = default;

        /// Получает уникальный ID комнаты
        [[nodiscard]] std::size_t get_id() const noexcept;

        [[nodiscard]] const std::string& get_name() const noexcept;
        [[nodiscard]] int get_room_number() const noexcept;
        [[nodiscard]] RoomType get_room_type() const noexcept;

        [[nodiscard]] std::string to_string() const override;

        /// Преобразует тип комнаты в строку
        static std::string room_type_to_string(RoomType type);

    private:
        static std::atomic<std::size_t> next_id_;
        const std::size_t id_;
        std::string name_;
        int room_number_;
        RoomType room_type_;
    };

    Speaker(const std::string& speaker_name, const std::string& room_name, int room_number, Room::RoomType room_type);

    // Запрещаем копирование, разрешаем перемещение
    Speaker(const Speaker&) = delete;
    Speaker& operator=(const Speaker&) = delete;
    Speaker(Speaker&&) = default;
    Speaker& operator=(Speaker&&) = default;

    /// Получает уникальный ID колонки
    [[nodiscard]] std::size_t get_id() const noexcept;

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

    [[nodiscard]] Room::RoomType get_room_type() const noexcept;
    [[nodiscard]] std::size_t get_device_count() const noexcept;
    [[nodiscard]] const Room& get_room() const noexcept;
    [[nodiscard]] std::string to_string() const override;

private:
    static std::atomic<std::size_t> next_id_;
    const std::size_t id_;
    std::string name_;
    std::map<std::string, std::shared_ptr<Device>> devices_;
    Room room_;
};

} // namespace smart_house 