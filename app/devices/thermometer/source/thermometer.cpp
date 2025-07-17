// Термометр - будет реализован позже
#include "thermometer.h"
#include <sstream>
#include <random>
 
namespace smart_house {

    Thermometer::Thermometer(const Thermometer& other)
        : Device(other.get_name()),
          temperature_(other.temperature_),
          is_calibrated_(other.is_calibrated_),
          temp_manager_(other.temp_manager_) {}

    Thermometer::Thermometer(Thermometer&& other) noexcept
        : Device(std::move(other)),
          temperature_(other.temperature_),
          is_calibrated_(other.is_calibrated_),
          temp_manager_(std::move(other.temp_manager_)) {}

    Thermometer& Thermometer::operator=(Thermometer&& other) noexcept {
        if (this != &other) {
            Device::operator=(std::move(other));
            temperature_ = other.temperature_;
            is_calibrated_ = other.is_calibrated_;
            temp_manager_ = std::move(other.temp_manager_);
        }
        return *this;
    }

    double Thermometer::read_value() const noexcept {
        return temperature_;
    }

    const std::string& Thermometer::get_unit() const noexcept {
        return temp_manager_.get_unit_string();
    }

    bool Thermometer::get_is_calibrated() const noexcept {
        return is_calibrated_;
    }

    void Thermometer::calibrate() {
        // Калибровка - сначала сбрасываем в 0, потом выполняем измерение
        temperature_ = 0.0;
        simulate_measurement();
        is_calibrated_ = true;
    }

    void Thermometer::set_temperature_unit(TemperatureUnit unit) noexcept {
        temp_manager_.set_unit(unit);
    }

    void Thermometer::simulate_measurement() {
        // Имитируем измерение температуры в диапазоне 15-30°C
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<double> dis(15.0, 30.0);
        
        temperature_ = dis(gen);
    }

    std::shared_ptr<Device> Thermometer::clone() const {
        return std::make_shared<Thermometer>(*this);
    }

    std::string Thermometer::to_string() const {
        std::stringstream ss;
        ss << "Thermometer: " << get_name() << " (ID: " << get_id() << ")";
        ss << " - Status: " << (get_status() == Device::DeviceStatus::ONLINE ? "ONLINE" : "OFFLINE");
        ss << ", Temperature: " << temperature_ << " " << temp_manager_.get_unit_string();
        ss << ", Calibrated: " << (is_calibrated_ ? "Yes" : "No");
        return ss.str();
    }

} // namespace smart_house 