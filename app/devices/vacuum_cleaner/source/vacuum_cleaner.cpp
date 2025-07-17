// Пылесос - будет реализован позже
#include "vacuum_cleaner.h"
#include <sstream>
#include <chrono>
#include <thread>
 
namespace smart_house {

    VacuumCleaner::VacuumCleaner(const VacuumCleaner& other)
        : Device(other.get_name()),
          power_state_(other.power_state_.load()),
          battery_level_(other.battery_level_.load()),
          on_dock_(other.on_dock_.load()) {}

    VacuumCleaner::VacuumCleaner(VacuumCleaner&& other) noexcept
        : Device(std::move(other)),
          power_state_(other.power_state_.load()),
          battery_level_(other.battery_level_.load()),
          on_dock_(other.on_dock_.load()) {
        other.power_state_.store(IActivatable::PowerState::OFF);
        other.on_dock_.store(false);
    }

    VacuumCleaner& VacuumCleaner::operator=(VacuumCleaner&& other) noexcept {
        if (this != &other) {
            Device::operator=(std::move(other));
            power_state_.store(other.power_state_.load());
            battery_level_.store(other.battery_level_.load());
            on_dock_.store(other.on_dock_.load());
            other.power_state_.store(IActivatable::PowerState::OFF);
            other.on_dock_.store(false);
        }
        return *this;
    }

    void VacuumCleaner::turn_on() noexcept {
        if (battery_level_.load() > MIN_BATTERY_FOR_WORK) {
            power_state_.store(IActivatable::PowerState::ON);
            undock(); // Пылесос автоматически сходит с базы при запуске
            work_async(); // Запускаем асинхронную работу
        } else {
            power_state_.store(IActivatable::PowerState::OFF);
        }
    }

    void VacuumCleaner::turn_off() noexcept {
        power_state_.store(IActivatable::PowerState::OFF);
        // Если пылесос на базе, начинаем зарядку
        if (on_dock_.load()) {
            charge_async();
        }
    }

    IActivatable::PowerState VacuumCleaner::get_power_state() const noexcept {
        return power_state_.load();
    }

    int VacuumCleaner::get_battery_level() const noexcept {
        return battery_level_.load();
    }
    
    bool VacuumCleaner::is_on_dock() const noexcept {
        return on_dock_.load();
    }
    
    void VacuumCleaner::dock() noexcept {
        // Если пылесос работает, имитируем поездку на базу
        if (power_state_.load() == IActivatable::PowerState::ON) {
            // Имитируем поездку на базу
            std::this_thread::sleep_for(std::chrono::seconds(1));
            power_state_.store(IActivatable::PowerState::OFF);
        }
        
        on_dock_.store(true);
        // Начинаем зарядку
        charge_async();
    }
    
    void VacuumCleaner::undock() noexcept {
        on_dock_.store(false);
        // Останавливаем зарядку, если она идет
        if (charge_future_.valid()) {
            charge_future_.wait();
        }
    }

    std::shared_ptr<Device> VacuumCleaner::clone() const {
        auto new_vacuum = std::make_shared<VacuumCleaner>(get_name());
        new_vacuum->power_state_.store(power_state_.load());
        new_vacuum->battery_level_.store(battery_level_.load());
        new_vacuum->on_dock_.store(on_dock_.load());
        return new_vacuum;
    }

    std::string VacuumCleaner::to_string() const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        std::ostringstream oss;
        oss << "VacuumCleaner[" << get_id() << "] '" << get_name() << "' - ";
        oss << "Power: " << (power_state_.load() == IActivatable::PowerState::ON ? "ON" : "OFF") << ", ";
        oss << "Battery: " << battery_level_.load() << "%, ";
        oss << "Dock: " << (on_dock_.load() ? "ON" : "OFF");
        return oss.str();
    }

    std::future<void> VacuumCleaner::work_async() {
        return std::async(std::launch::async, [this]() {
            try {
                while (power_state_.load() == IActivatable::PowerState::ON && 
                       battery_level_.load() > 0) {
                    // Расходуем батарею на 10% за каждую "работу"
                    int current_battery = battery_level_.load();
                    battery_level_.store(std::max(0, current_battery - 10));
                    
                    // Если батарея разрядилась, выключаем пылесос
                    if (battery_level_.load() == 0) {
                        power_state_.store(IActivatable::PowerState::OFF);
                        // Если пылесос на базе, начинаем зарядку
                        if (on_dock_.load()) {
                            charge_async();
                        }
                        break;
                    }
                    
                    // Если заряд стал низким, автоматически возвращаемся на базу
                    if (battery_level_.load() <= MIN_BATTERY_FOR_WORK && !on_dock_.load()) {
                        // Автоматически возвращаемся на базу
                        dock();
                        break;
                    }
                    
                    // Имитируем работу - ждем 2 секунды
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }
            } catch (...) {
                power_state_.store(IActivatable::PowerState::OFF);
            }
        });
    }
    
    std::future<void> VacuumCleaner::charge_async() {
        // Если уже идет зарядка, не запускаем новую
        if (charge_future_.valid() && charge_future_.wait_for(std::chrono::milliseconds(0)) != std::future_status::ready) {
            return std::future<void>{}; // Возвращаем пустое future
        }
        
        charge_future_ = std::async(std::launch::async, [this]() {
            try {
                while (on_dock_.load() && 
                       power_state_.load() == IActivatable::PowerState::OFF && 
                       battery_level_.load() < 100) {
                    // Заряжаем батарею на 5% за каждую "зарядку"
                    int current_battery = battery_level_.load();
                    battery_level_.store(std::min(100, current_battery + 5));
                    
                    // Имитируем зарядку - ждем 1 секунду
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            } catch (...) {
                // Игнорируем исключения при зарядке
            }
        });
        
        return std::future<void>{}; // Возвращаем пустое future, так как charge_future_ уже сохранен
    }

} // namespace smart_house 