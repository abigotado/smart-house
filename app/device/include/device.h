#pragma once

#include <string>
#include <memory>

namespace smart_house {
    class Device {
        public:
            enum class DeviceStatus { ONLINE, OFFLINE };

            Device(const std::string& id, const std::string& name);
            virtual ~Device() = default;

            [[nodiscard]] const std::string& get_id() const noexcept;
            [[nodiscard]] const std::string& get_name() const noexcept;
            [[nodiscard]] const DeviceStatus get_status() const noexcept;
            void set_status(DeviceStatus status) noexcept;

            virtual std::shared_ptr<Device> clone() const = 0;
            virtual std::string to_string() const = 0;


        protected:
            const std::string id;
            const std::string name;
            DeviceStatus status = DeviceStatus::OFFLINE;
    };
}