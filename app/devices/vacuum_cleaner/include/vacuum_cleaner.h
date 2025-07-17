#pragma once

#include "../../device/include/device.h"
#include "../../../shared/include/activatable.h"
#include <shared_mutex>
#include <atomic>
#include <future>

namespace smart_house {

/**
 * @brief Робот-пылесос с аккумулятором
 */
class VacuumCleaner : public Device, public IActivatable {
    public:
        using Device::Device;

        /// Конструктор копирования
        VacuumCleaner(const VacuumCleaner& other);
        
        VacuumCleaner(VacuumCleaner&& other) noexcept;
        VacuumCleaner& operator=(VacuumCleaner&& other) noexcept;

        // Интерфейс IActivatable
        void turn_on() noexcept override;
        void turn_off() noexcept override;
        [[nodiscard]] IActivatable::PowerState get_power_state() const noexcept override;
        
        std::string to_string() const override;
        
        [[nodiscard]] int get_battery_level() const noexcept;
        
        /// Проверяет, находится ли пылесос на базе
        [[nodiscard]] bool is_on_dock() const noexcept;
        
        /// Ставит пылесос на базу
        void dock() noexcept;

        /// Создает копию устройства
        std::shared_ptr<Device> clone() const override;

    private:
        /// Асинхронная работа пылесоса
        std::future<void> work_async();
        
        /// Асинхронная зарядка пылесоса
        std::future<void> charge_async();
        
        /// Убирает пылесос с базы (приватный, вызывается автоматически при работе)
        void undock() noexcept;
        
        /// Минимальный заряд для продолжения работы (в процентах)
        static constexpr int MIN_BATTERY_FOR_WORK = 20;
        
        mutable std::shared_mutex mutex_;  // Read-write мьютекс для защиты данных
        std::atomic<IActivatable::PowerState> power_state_{IActivatable::PowerState::OFF};
        std::atomic<int> battery_level_{100};
        std::atomic<bool> on_dock_{false};
        std::future<void> charge_future_;  // Будущее для асинхронной зарядки
};

} // namespace smart_house 