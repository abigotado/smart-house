#pragma once

#include <string>
#include <memory>
#include "../../../shared/include/object.h"

namespace smart_house {
    class Device : public Object {
        public:
            enum class DeviceStatus { ONLINE, OFFLINE };

            // Конструкторы и деструкторы
            Device(const std::string& id, const std::string& name);
            virtual ~Device() = default;

            // Геттеры и сеттеры
            [[nodiscard]] const std::string& get_id() const noexcept;
            [[nodiscard]] const std::string& get_name() const noexcept;
            [[nodiscard]] const DeviceStatus get_status() const noexcept;
            void set_status(DeviceStatus status) noexcept;

            // Виртуальные методы
            virtual std::shared_ptr<Device> clone() const = 0;
            // to_string() наследуется от Object


        protected:
            const std::string id;
            const std::string name;
            DeviceStatus status = DeviceStatus::OFFLINE;
    };
}