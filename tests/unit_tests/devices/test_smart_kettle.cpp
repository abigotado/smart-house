#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "../../../app/devices/smart_kettle/include/smart_kettle.h"
#include <thread>
#include <chrono>

using namespace smart_house;

TEST_CASE("SmartKettle basic properties", "[kettle]") {
    SmartKettle kettle("TestKettle", TemperatureUnit::CELSIUS);
    REQUIRE(kettle.get_name() == "TestKettle");
    REQUIRE(kettle.get_power_state() == IActivatable::PowerState::OFF);
    REQUIRE(kettle.read_value() == Catch::Approx(20.0));
    REQUIRE(kettle.get_is_calibrated() == true);
    REQUIRE(kettle.get_unit() == "°C");
}

TEST_CASE("SmartKettle heating and auto-off", "[kettle]") {
    SmartKettle kettle("TestKettle");
    kettle.set_target_temperature(23.0);
    kettle.turn_on();
    // Ждем до 5 секунд, пока чайник не нагреется
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (kettle.get_power_state() == IActivatable::PowerState::OFF)
            break;
    }
    REQUIRE(kettle.read_value() >= 23.0);
    REQUIRE(kettle.get_power_state() == IActivatable::PowerState::OFF);
}

TEST_CASE("SmartKettle copy and clone", "[kettle]") {
    SmartKettle kettle("TestKettle");
    kettle.set_target_temperature(30.0);
    kettle.turn_on();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    SmartKettle copy = kettle;
    auto clone = kettle.clone();
    REQUIRE(copy.read_value() == Catch::Approx(kettle.read_value()));
    auto clone_kettle = std::dynamic_pointer_cast<SmartKettle>(clone);
    REQUIRE(clone_kettle->read_value() == Catch::Approx(kettle.read_value()));
    REQUIRE(copy.get_name() == kettle.get_name());
    REQUIRE(clone->get_name() == kettle.get_name());
    REQUIRE(copy.get_id() != kettle.get_id());
    REQUIRE(clone->get_id() != kettle.get_id());
}

TEST_CASE("SmartKettle unit switching", "[kettle]") {
    SmartKettle kettle("TestKettle");
    kettle.set_temperature_unit(TemperatureUnit::FAHRENHEIT);
    REQUIRE(kettle.get_unit() == "°F");
    kettle.set_temperature_unit(TemperatureUnit::KELVIN);
    REQUIRE(kettle.get_unit() == "K");
} 