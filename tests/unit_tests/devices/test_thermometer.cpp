#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "../../../app/devices/thermometer/include/thermometer.h"

using namespace smart_house;

TEST_CASE("Thermometer basic functionality", "[thermometer]") {
    Thermometer thermometer("Тестовый термометр");
    
    SECTION("Initial state") {
        REQUIRE(thermometer.get_is_calibrated() == false);
        REQUIRE(thermometer.get_unit() == "°C");
        REQUIRE(!thermometer.get_id().empty());
        REQUIRE(thermometer.get_name() == "Тестовый термометр");
    }
    
    SECTION("Temperature reading") {
        double temp = thermometer.read_value();
        REQUIRE(temp >= -50.0);
        REQUIRE(temp <= 50.0);
    }
    
    SECTION("Calibration") {
        thermometer.calibrate();
        REQUIRE(thermometer.get_is_calibrated() == true);
        
        // После калибровки выполняется simulate_measurement(), температура не 0
        double temp = thermometer.read_value();
        REQUIRE(temp >= 15.0);
        REQUIRE(temp <= 30.0);
    }
    
    SECTION("Unit conversion") {
        thermometer.set_temperature_unit(TemperatureUnit::FAHRENHEIT);
        REQUIRE(thermometer.get_unit() == "°F");
        
        thermometer.set_temperature_unit(TemperatureUnit::KELVIN);
        REQUIRE(thermometer.get_unit() == "K");
        
        thermometer.set_temperature_unit(TemperatureUnit::CELSIUS);
        REQUIRE(thermometer.get_unit() == "°C");
    }
}

TEST_CASE("Thermometer copying and moving", "[thermometer]") {
    Thermometer original("Оригинал");
    original.set_status(Device::DeviceStatus::ONLINE);
    original.calibrate();
    original.set_temperature_unit(TemperatureUnit::FAHRENHEIT);
    
    SECTION("Copying") {
        Thermometer copy(original);
        REQUIRE(copy.get_name() == "Оригинал");
        REQUIRE(copy.get_id() != original.get_id());
        REQUIRE(copy.get_status() == Device::DeviceStatus::OFFLINE); // Дефолтный статус
        REQUIRE(copy.get_is_calibrated() == true);
        REQUIRE(copy.get_unit() == "°F");
    }
    
    SECTION("Moving") {
        Thermometer moved(std::move(original));
        REQUIRE(moved.get_name() == "Оригинал");
        REQUIRE(moved.get_id() != original.get_id());
        REQUIRE(moved.get_is_calibrated() == true);
        REQUIRE(moved.get_unit() == "°F");
        
        // Оригинал должен быть в неопределенном состоянии
        REQUIRE(original.get_status() == Device::DeviceStatus::OFFLINE);
    }
    
    SECTION("Cloning") {
        auto clone = original.clone();
        REQUIRE(clone->get_name() == "Оригинал");
        REQUIRE(clone->get_id() != original.get_id());
        REQUIRE(clone->get_status() == Device::DeviceStatus::OFFLINE); // Дефолтный статус
    }
} 