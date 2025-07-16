#pragma once

#include <string>
#include <memory>
#include <random>
#include <sstream>
#include <iomanip>
#include "../../../shared/include/object.h"

namespace smart_house {

/**
 * @brief Генерирует UUID для устройств
 */
std::string generate_device_uuid();

/**
 * @brief Базовый класс для всех устройств умного дома
 */
class Device : public Object {
        public:
            enum class DeviceStatus { ONLINE, OFFLINE };

            Device(const std::string& name);
            virtual ~Device() = default;

            // Разрешаем копирование (для clone())
            Device(const Device& other);
            
            // Запрещаем присваивание копированием
            Device& operator=(const Device&) = delete;
            
            // Разрешаем перемещение
            Device(Device&&) = default;
            Device& operator=(Device&&) = default;

            [[nodiscard]] const std::string& get_id() const noexcept;
            [[nodiscard]] const std::string& get_name() const noexcept;
            [[nodiscard]] DeviceStatus get_status() const noexcept;
            void set_status(DeviceStatus status) noexcept;

        /// Создает копию устройства
            virtual std::shared_ptr<Device> clone() const = 0;

        protected:
            const std::string id_;
            const std::string name_;
            DeviceStatus status_ = DeviceStatus::OFFLINE;
    };

}