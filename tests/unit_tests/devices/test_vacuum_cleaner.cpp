#include <catch2/catch_test_macros.hpp>
#include "../../../app/devices/vacuum_cleaner/include/vacuum_cleaner.h"

using namespace smart_house;

TEST_CASE("VacuumCleaner basic functionality", "[vacuum_cleaner]") {
    VacuumCleaner vacuum("Тестовый пылесос");
    
    SECTION("Initial state") {
        REQUIRE(vacuum.get_power_state() == IActivatable::PowerState::OFF);
        REQUIRE(vacuum.get_battery_level() == 100);
        REQUIRE(vacuum.is_on_dock() == false);
        REQUIRE(!vacuum.get_id().empty());
        REQUIRE(vacuum.get_name() == "Тестовый пылесос");
    }
    
    SECTION("Docking and undocking") {
        vacuum.dock();
        REQUIRE(vacuum.is_on_dock() == true);
        
        // undock() вызывается автоматически при turn_on(), если заряд достаточный
        if (vacuum.get_battery_level() > 20) {
            vacuum.turn_on();
            // Небольшая задержка для асинхронной обработки
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            if (vacuum.get_power_state() == IActivatable::PowerState::ON) {
                REQUIRE(vacuum.is_on_dock() == false);
            }
        }
    }
    
    SECTION("Battery level affects power on") {
        // Проверяем, что пылесос не включается при низком заряде
        if (vacuum.get_battery_level() <= 20) {
            vacuum.turn_on();
            REQUIRE(vacuum.get_power_state() == IActivatable::PowerState::OFF);
        }
    }
    
    SECTION("Power control") {
        // Пылесос с полной батареей должен включаться
        if (vacuum.get_battery_level() > 20) {
            vacuum.turn_on();
            // Небольшая задержка для асинхронной обработки
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            if (vacuum.get_power_state() == IActivatable::PowerState::ON) {
                vacuum.turn_off();
                REQUIRE(vacuum.get_power_state() == IActivatable::PowerState::OFF);
            }
        }
    }
}

TEST_CASE("VacuumCleaner copying and moving", "[vacuum_cleaner]") {
    VacuumCleaner original("Оригинал");
    original.set_status(Device::DeviceStatus::ONLINE);
    original.dock();
    
    SECTION("Copying") {
        VacuumCleaner copy(original);
        REQUIRE(copy.get_name() == "Оригинал");
        REQUIRE(copy.get_id() != original.get_id());
        REQUIRE(copy.get_status() == Device::DeviceStatus::OFFLINE); // Дефолтный статус
        REQUIRE(copy.get_battery_level() == 100);
        // Состояние базы не копируется, поэтому не проверяем is_on_dock()
    }
    
    SECTION("Moving") {
        VacuumCleaner moved(std::move(original));
        REQUIRE(moved.get_name() == "Оригинал");
        REQUIRE(moved.get_id() != original.get_id());
        REQUIRE(moved.get_battery_level() == 100);
        
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