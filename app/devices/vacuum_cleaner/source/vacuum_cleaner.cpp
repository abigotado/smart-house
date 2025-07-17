// Пылесос - будет реализован позже
#include "vacuum_cleaner.h"
 
// Временная заглушка для компиляции
namespace smart_house {
    // Реализация будет добавлена позже

    VacuumCleaner::VacuumCleaner(VacuumCleaner&& other) noexcept
        : Device(std::move(other)),
          power_state_(other.power_state_),
          battery_level_(other.battery_level_) {}

    VacuumCleaner& VacuumCleaner::operator=(VacuumCleaner&& other) noexcept {
        if (this != &other) {
            Device::operator=(std::move(other));
            power_state_ = other.power_state_;
            battery_level_ = other.battery_level_;
        }
        return *this;
    }
} 