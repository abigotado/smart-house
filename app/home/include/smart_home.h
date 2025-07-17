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
    [[nodiscard]] const std::string& get_id() const noexcept;

    /// Добавляет колонку
    bool add_speaker(const std::string& name, const Speaker::Room& room);

    /// Перемещает колонку в другую комнату
    bool move_speaker(const std::string& name, const Speaker::Room& new_room);

    /// Переименовывает колонку
    bool rename_speaker(const std::string& old_name, const std::string& new_name);

    /// Удаляет колонку по имени
    bool remove_speaker(const std::string& name);

    /// Возвращает количество колонок
    [[nodiscard]] std::size_t size() const noexcept;

    /// Возвращает константную ссылку на все колонки
    [[nodiscard]] const std::map<std::string, Speaker>& get_speakers() const noexcept;

    [[nodiscard]] std::string to_string() const override;

    /// Доступ к колонке по имени
    [[nodiscard]] Speaker& operator[](const std::string& name);
    [[nodiscard]] const Speaker& operator[](const std::string& name) const;

    /// Вывод в поток (сортированный список колонок)
    friend std::ostream& operator<<(std::ostream& os, const SmartHome& smart_home);

private:
    std::string id_;
    std::map<std::string, Speaker> speakers_;
};

} // namespace smart_house 