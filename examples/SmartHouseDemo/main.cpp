#include <iostream>
#include <memory>
#include "../../app/home/include/smart_home.h"
#include "../../app/speaker/include/speaker.h"
#include "../../app/devices/vacuum_cleaner/include/vacuum_cleaner.h"
#include "../../app/devices/smart_light/include/smart_light.h"
#include "../../app/devices/thermometer/include/thermometer.h"
#include "../../app/devices/smart_kettle/include/smart_kettle.h"

using namespace smart_house;

int main() {
    // Создаём умный дом
    SmartHome home;

    // Добавляем две колонки
    Speaker::Room living_room{"Гостиная", 1, Speaker::RoomType::LIVING_ROOM};
    Speaker::Room kitchen{"Кухня", 2, Speaker::RoomType::KITCHEN};
    home.add_speaker("Алиса", living_room);
    home.add_speaker("Маруся", kitchen);

    // Добавляем устройства в колонку Alice
    auto& alice = home["Алиса"];
    alice.add_device(std::make_shared<VacuumCleaner>("Пылесос"));
    alice.add_device(std::make_shared<SmartLight>("Люстра"));
    alice.add_device(std::make_shared<Thermometer>("Термометр"));

    // Добавляем устройства в колонку Bob
    auto& bob = home["Маруся"];
    bob.add_device(std::make_shared<SmartKettle>("Чайник"));
    bob.add_device(std::make_shared<SmartLight>("Подсветка"));

    // Включаем все устройства в Alice
    std::cout << "\nОбход и активация устройств в колонке Alice:" << std::endl;
    alice.check_and_activate_devices();

    // Выводим состояние умного дома
    std::cout << "\nСостояние умного дома:" << std::endl;
    std::cout << home << std::endl;

    // Демонстрируем работу пылесоса
    auto vacuum = alice.get_device("Пылесос");
    if (vacuum) {
        std::cout << "\nВключаем пылесос..." << std::endl;
        std::dynamic_pointer_cast<VacuumCleaner>(vacuum)->turn_on();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << std::dynamic_pointer_cast<VacuumCleaner>(vacuum)->to_string() << std::endl;
        std::cout << "Ставим пылесос на базу..." << std::endl;
        std::dynamic_pointer_cast<VacuumCleaner>(vacuum)->dock();
        std::cout << std::dynamic_pointer_cast<VacuumCleaner>(vacuum)->to_string() << std::endl;
    }

    return 0;
} 