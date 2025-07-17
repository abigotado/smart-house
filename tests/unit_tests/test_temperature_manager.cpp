#include <catch2/catch_test_macros.hpp>
#include "../../app/temperature_manager/include/temperature_manager.h"

using namespace smart_house;

TEST_CASE("TemperatureManager basic functionality", "[temperature_manager]") {
    TemperatureManager manager(TemperatureUnit::CELSIUS);
    
    SECTION("Default unit") {
        REQUIRE(manager.get_unit() == TemperatureUnit::CELSIUS);
        REQUIRE(manager.get_unit_string() == "°C");
    }
    
    SECTION("Set and get unit") {
        manager.set_unit(TemperatureUnit::FAHRENHEIT);
        REQUIRE(manager.get_unit() == TemperatureUnit::FAHRENHEIT);
        REQUIRE(manager.get_unit_string() == "°F");
        
        manager.set_unit(TemperatureUnit::KELVIN);
        REQUIRE(manager.get_unit() == TemperatureUnit::KELVIN);
        REQUIRE(manager.get_unit_string() == "K");
    }
} 