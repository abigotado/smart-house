#include <catch2/catch_test_macros.hpp>
#include "../../app/speaker/include/speaker.h"
#include "../../app/devices/smart_light/include/smart_light.h"
#include "../../app/devices/vacuum_cleaner/include/vacuum_cleaner.h"

using namespace smart_house;

TEST_CASE("Speaker basic functionality", "[speaker]") {
    Speaker::Room room{"Тестовая комната", 1, Speaker::RoomType::LIVING_ROOM};
    Speaker speaker("Тестовая колонка", room);
    
    SECTION("Basic properties") {
        REQUIRE(speaker.get_name() == "Тестовая колонка");
        REQUIRE(speaker.get_room_type() == Speaker::RoomType::LIVING_ROOM);
        REQUIRE(speaker.get_device_count() == 0);
        REQUIRE(speaker.get_room().name == "Тестовая комната");
    }
    
    SECTION("Adding devices") {
        auto vacuum = std::make_shared<VacuumCleaner>("Пылесос");
        auto light = std::make_shared<SmartLight>("Лампа");
        
        REQUIRE(speaker.add_device(vacuum) == true);
        REQUIRE(speaker.add_device(light) == true);
        REQUIRE(speaker.get_device_count() == 2);
    }
    
    SECTION("Getting devices") {
        auto device = std::make_shared<SmartLight>("Тестовая лампа");
        speaker.add_device(device);
        
        auto retrieved = speaker.get_device(device->get_id());
        REQUIRE(retrieved != nullptr);
        REQUIRE(retrieved->get_name() == "Тестовая лампа");
    }
    
    SECTION("Removing devices") {
        auto device = std::make_shared<SmartLight>("Тестовая лампа");
        speaker.add_device(device);
        
        REQUIRE(speaker.remove_device(device->get_id()) == true);
        REQUIRE(speaker.get_device_count() == 0);
    }
    
    SECTION("Getting all devices") {
        auto device1 = std::make_shared<SmartLight>("Лампа1");
        auto device2 = std::make_shared<SmartLight>("Лампа2");
        
        speaker.add_device(device1);
        speaker.add_device(device2);
        
        const auto& devices = speaker.get_all_devices();
        REQUIRE(devices.size() == 2);
        REQUIRE(devices.find(device1->get_id()) != devices.end());
        REQUIRE(devices.find(device2->get_id()) != devices.end());
    }
} 