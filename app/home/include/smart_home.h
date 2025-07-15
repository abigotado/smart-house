#pragma once

#include "../../shared/include/object.h"
#include "../../speaker/include/speaker.h"
#include <map>
#include <string>
#include <iostream>
#include <atomic>

namespace smart_house {

/**
 * @brief Система умного дома - управляет несколькими умными колонками
 */
class SmartHome : public Object {
public:
    SmartHome();
    
    // Запрещаем копирование и перемещение
    SmartHome(const SmartHome&) = delete;
    SmartHome& operator=(const SmartHome&) = delete;
    SmartHome(SmartHome&&) = delete;
    SmartHome& operator=(SmartHome&&) = delete;

    /// Получает уникальный ID дома
    [[nodiscard]] std::size_t get_id() const noexcept;

    /// Добавляет колонку
    bool add_speaker(const std::string& name, const std::string& room_name, 
                     int room_number, Speaker::Room::RoomType room_type);

    /// Удаляет колонку по имени
    bool remove_speaker(const std::string& name);

    /// Возвращает количество колонок
    [[nodiscard]] std::size_t size() const noexcept;

    [[nodiscard]] std::string to_string() const override;

    /// Доступ к колонке по имени
    [[nodiscard]] Speaker& operator[](const std::string& name);
    [[nodiscard]] const Speaker& operator[](const std::string& name) const;

    /// Доступ к колонке по индексу
    [[nodiscard]] Speaker& operator[](std::size_t index);
    [[nodiscard]] const Speaker& operator[](std::size_t index) const;

    /// Вывод в поток (сортированный список колонок)
    friend std::ostream& operator<<(std::ostream& os, const SmartHome& smart_home);

private:
    static std::atomic<std::size_t> next_id_;
    const std::size_t id_;
    std::map<std::string, Speaker> speakers_;
};

} // namespace smart_house 