#include <catch2/catch_test_macros.hpp>
#include "../../../app/devices/smart_light/include/smart_light.h"

using namespace smart_house;

TEST_CASE("SmartLight basic functionality", "[smart_light]") {
    SmartLight light("Тестовая лампа");
    
    SECTION("Initial state") {
        REQUIRE(light.get_power_state() == IActivatable::PowerState::OFF);
        REQUIRE(light.get_brightness() == 100);
        REQUIRE(light.get_name() == "Тестовая лампа");
        REQUIRE(!light.get_id().empty());
    }
    
    SECTION("Power control") {
        light.turn_on();
        REQUIRE(light.get_power_state() == IActivatable::PowerState::ON);
        
        light.turn_off();
        REQUIRE(light.get_power_state() == IActivatable::PowerState::OFF);
    }
    
    SECTION("Brightness control") {
        light.set_brightness(50);
        REQUIRE(light.get_brightness() == 50);
        
        light.set_brightness(0);
        REQUIRE(light.get_brightness() == 0);
        
        light.set_brightness(100);
        REQUIRE(light.get_brightness() == 100);
        
        // Некорректные значения не должны изменять яркость
        light.set_brightness(-10);
        REQUIRE(light.get_brightness() == 100);
        
        light.set_brightness(150);
        REQUIRE(light.get_brightness() == 100);
    }
    
    SECTION("Brightness can be set regardless of power state") {
        light.set_brightness(30);
        REQUIRE(light.get_brightness() == 30);
        
        light.turn_on();
        REQUIRE(light.get_brightness() == 30);
        
        light.set_brightness(70);
        REQUIRE(light.get_brightness() == 70);
    }
}

TEST_CASE("SmartLight copying and moving", "[smart_light]") {
    SmartLight original("Оригинал");
    original.set_status(Device::DeviceStatus::ONLINE);
    original.turn_on();
    original.set_brightness(50);
    
    SECTION("Copying") {
        SmartLight copy(original);
        REQUIRE(copy.get_name() == "Оригинал");
        REQUIRE(copy.get_id() != original.get_id());
        REQUIRE(copy.get_status() == Device::DeviceStatus::OFFLINE); // Дефолтный статус
        REQUIRE(copy.get_power_state() == IActivatable::PowerState::ON);
        REQUIRE(copy.get_brightness() == 50);
    }
    
    SECTION("Moving") {
        SmartLight moved(std::move(original));
        REQUIRE(moved.get_name() == "Оригинал");
        REQUIRE(moved.get_id() != original.get_id());
        REQUIRE(moved.get_power_state() == IActivatable::PowerState::ON);
        REQUIRE(moved.get_brightness() == 50);
        
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