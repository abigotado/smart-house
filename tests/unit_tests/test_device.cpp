#include <catch2/catch_test_macros.hpp>
#include "../../app/devices/device/include/device.h"

using namespace smart_house;

class DummyDevice : public Device {
public:
    DummyDevice(const std::string& name) : Device(name) {}
    std::shared_ptr<Device> clone() const override {
        return std::make_shared<DummyDevice>(*this);
    }
    std::string to_string() const override {
        return "DummyDevice: " + get_name() + " (ID: " + get_id() + ")";
    }
};

TEST_CASE("Device base class functionality", "[device]") {
    DummyDevice device("Тестовое устройство");
    
    SECTION("Basic properties") {
        REQUIRE(device.get_name() == "Тестовое устройство");
        REQUIRE(!device.get_id().empty());
        REQUIRE(device.get_status() == Device::DeviceStatus::OFFLINE);
    }
    
    SECTION("Status change") {
        device.set_status(Device::DeviceStatus::ONLINE);
        REQUIRE(device.get_status() == Device::DeviceStatus::ONLINE);
    }
    
    SECTION("Copying and moving") {
        DummyDevice copy(device);
        REQUIRE(copy.get_name() == device.get_name());
        REQUIRE(copy.get_id() != device.get_id());
        REQUIRE(copy.get_status() == Device::DeviceStatus::OFFLINE);
        
        DummyDevice moved(std::move(device));
        REQUIRE(moved.get_name() == "Тестовое устройство");
        REQUIRE(moved.get_status() == Device::DeviceStatus::OFFLINE);
    }
    
    SECTION("Cloning") {
        auto clone = device.clone();
        REQUIRE(clone->get_name() == device.get_name());
        REQUIRE(clone->get_id() != device.get_id());
        REQUIRE(clone->get_status() == Device::DeviceStatus::OFFLINE);
    }
} 