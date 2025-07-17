#include "smart_kettle.h"
#include <sstream>
#include <iomanip>
#include <chrono>
#include <thread>

namespace smart_house {
    
    SmartKettle::SmartKettle(const std::string& name, TemperatureUnit unit)
        : Device(name), temp_manager_(unit) {}

    SmartKettle::SmartKettle(const SmartKettle& other)
        : Device(other.get_name()), // генерирует новый id
          power_state_(other.power_state_.load()),
          temperature_(other.temperature_.load()),
          calibrated_(other.calibrated_.load()),
          target_temp_(other.target_temp_.load()),
          temp_manager_(other.temp_manager_),
          unit_string_cache_(other.unit_string_cache_)
    {
        // mutex_ не копируется, создаётся новый
    }
    
    SmartKettle::SmartKettle(SmartKettle&& other) noexcept
        : Device(std::move(other)),
          power_state_(other.power_state_.load()),
          temperature_(other.temperature_.load()),
          calibrated_(other.calibrated_.load()),
          target_temp_(other.target_temp_.load()),
          temp_manager_(std::move(other.temp_manager_)),
          unit_string_cache_(std::move(other.unit_string_cache_))
    {
        // mutex_ не перемещается, создаётся новый
        other.power_state_.store(IActivatable::PowerState::OFF);
    }

    SmartKettle& SmartKettle::operator=(SmartKettle&& other) noexcept {
        if (this != &other) {
            Device::operator=(std::move(other));
            power_state_.store(other.power_state_.load());
            temperature_.store(other.temperature_.load());
            calibrated_.store(other.calibrated_.load());
            target_temp_.store(other.target_temp_.load());
            temp_manager_ = std::move(other.temp_manager_);
            unit_string_cache_ = std::move(other.unit_string_cache_);
            // mutex_ не перемещается
            other.power_state_.store(IActivatable::PowerState::OFF);
        }
        return *this;
    }
    
    void SmartKettle::turn_on() noexcept {
        power_state_.store(IActivatable::PowerState::ON);
        // Запускаем нагрев в отдельном потоке после установки состояния
        heat();
    }
    
    void SmartKettle::turn_off() noexcept {
        power_state_.store(IActivatable::PowerState::OFF);
    }
    
    IActivatable::PowerState SmartKettle::get_power_state() const noexcept {
        return power_state_.load();
    }

    double SmartKettle::read_value() const noexcept {
        return temperature_.load();
    }

    const std::string& SmartKettle::get_unit() const noexcept {
        unit_string_cache_ = temp_manager_.get_unit_string();
        return unit_string_cache_;
    }

    bool SmartKettle::get_is_calibrated() const noexcept {
        return calibrated_.load();
    }

    void SmartKettle::calibrate() {
        // Простая калибровка - устанавливаем температуру в 20 градусов
        temperature_.store(20.0);
        calibrated_.store(true);
    }

    std::shared_ptr<Device> SmartKettle::clone() const {
        // Создаем новый объект с теми же параметрами
        auto new_kettle = std::make_shared<SmartKettle>(get_name());
        // Копируем состояние атомарных переменных
        new_kettle->power_state_.store(power_state_.load());
        new_kettle->temperature_.store(temperature_.load());
        new_kettle->calibrated_.store(calibrated_.load());
        new_kettle->target_temp_.store(target_temp_.load());
        new_kettle->unit_string_cache_ = unit_string_cache_;
        return new_kettle;
    }

    void SmartKettle::set_target_temperature(double temperature) {
        target_temp_.store(temperature);
    }

    double SmartKettle::get_target_temperature() const {
        return target_temp_.load();
    }

    void SmartKettle::set_temperature_unit(TemperatureUnit unit) noexcept {
        std::unique_lock lock(mutex_);
        auto old_unit = temp_manager_.get_unit();
        if (old_unit != unit) {
            // Конвертируем значения
            double temp = temperature_.load();
            double target = target_temp_.load();
            temperature_.store(TemperatureManager::convert(temp, old_unit, unit));
            target_temp_.store(TemperatureManager::convert(target, old_unit, unit));
            temp_manager_.set_unit(unit);
            unit_string_cache_.clear();
        }
    }

    std::string SmartKettle::to_string() const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        std::ostringstream oss;
        oss << "SmartKettle[" << get_id() << "] '" << get_name() << "' - ";
        oss << "Power: " << (power_state_.load() == IActivatable::PowerState::ON ? "ON" : "OFF") << ", ";
        oss << "Temperature: " << std::fixed << std::setprecision(1) << temperature_.load() << " " << get_unit() << ", ";
        oss << "Target: " << target_temp_.load() << " " << get_unit() << ", ";
        oss << "Calibrated: " << (calibrated_.load() ? "Yes" : "No");
        return oss.str();
    }
    
    std::future<void> SmartKettle::heat() {
        return std::async(std::launch::async, [this]() {
            try {
                while (true) {
                    // Проверяем, не выключили ли нас
                    if (power_state_.load() == IActivatable::PowerState::OFF) {
                        break;
                    }
                    // Проверяем, достигли ли целевой температуры
                    double current_temp = temperature_.load();
                    double target = target_temp_.load();
                    if (current_temp >= target) {
                        power_state_.store(IActivatable::PowerState::OFF);
                        break;
                    }
                    // Увеличиваем на 1 градус атомарно
                    temperature_.store(current_temp + 1.0);
                    // Ждем 1 секунду
                    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // уменьшено
                }
            } catch (...) {
                power_state_.store(IActivatable::PowerState::OFF);
            }
        });
    }
} 