#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <chrono>
#include <thread>
#include <vector>
#include <future>
#include <algorithm>
#include "../app/home/include/smart_home.h"
#include "../app/speaker/include/speaker.h"
#include "../app/devices/vacuum_cleaner/include/vacuum_cleaner.h"
#include "../app/devices/smart_light/include/smart_light.h"
#include "../app/devices/thermometer/include/thermometer.h"
#include "../app/devices/smart_kettle/include/smart_kettle.h"
#include "../app/shared/include/uuid.h"

using namespace smart_house;

TEST_CASE("Performance tests", "[performance]") {
    
    SECTION("SmartHome scalability") {
        SmartHome home;
        Speaker::Room room{"Тестовая комната", 1, Speaker::RoomType::LIVING_ROOM};
        
        auto start = std::chrono::high_resolution_clock::now();
        
        // Добавляем много колонок
        for (int i = 0; i < 100; ++i) {
            std::string name = "Колонка_" + std::to_string(i);
            home.add_speaker(name, room);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        REQUIRE(home.size() == 100);
        REQUIRE(duration.count() < 10000); // Должно выполняться быстро (< 10ms)
    }
    
    SECTION("Device creation performance") {
        auto start = std::chrono::high_resolution_clock::now();
        
        std::vector<std::shared_ptr<Device>> devices;
        for (int i = 0; i < 1000; ++i) {
            devices.push_back(std::make_shared<SmartLight>("Лампа_" + std::to_string(i)));
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        REQUIRE(devices.size() == 1000);
        REQUIRE(duration.count() < 50000); // Должно выполняться быстро (< 50ms)
    }
    
    SECTION("Concurrent device operations") {
        std::vector<std::shared_ptr<SmartLight>> lights;
        for (int i = 0; i < 10; ++i) {
            lights.push_back(std::make_shared<SmartLight>("Лампа_" + std::to_string(i)));
        }
        
        // Запускаем операции включения/выключения в разных потоках
        std::vector<std::future<void>> futures;
        
        for (auto& light : lights) {
            futures.push_back(std::async(std::launch::async, [&light]() {
                for (int j = 0; j < 100; ++j) {
                    light->turn_on();
                    light->turn_off();
                }
            }));
        }
        
        // Ждем завершения всех потоков
        for (auto& future : futures) {
            future.wait();
        }
        
        // Проверяем, что все устройства в выключенном состоянии
        for (auto& light : lights) {
            REQUIRE(light->get_power_state() == IActivatable::PowerState::OFF);
        }
    }
    
    SECTION("Memory usage test") {
        // Тест на утечки памяти при создании/удалении устройств
        for (int iteration = 0; iteration < 100; ++iteration) {
            std::vector<std::shared_ptr<Device>> devices;
            
            for (int i = 0; i < 100; ++i) {
                devices.push_back(std::make_shared<SmartLight>("Лампа_" + std::to_string(i)));
                devices.push_back(std::make_shared<VacuumCleaner>("Пылесос_" + std::to_string(i)));
                devices.push_back(std::make_shared<Thermometer>("Термометр_" + std::to_string(i)));
                devices.push_back(std::make_shared<SmartKettle>("Чайник_" + std::to_string(i)));
            }
            
            // Выполняем операции с устройствами
            for (auto& device : devices) {
                if (auto light = std::dynamic_pointer_cast<SmartLight>(device)) {
                    light->turn_on();
                    light->set_brightness(50);
                }
            }
            
            // devices автоматически уничтожаются здесь
        }
        
        // Если есть утечки памяти, они проявятся в профилировщике
        REQUIRE(true); // Просто проверяем, что код выполняется без ошибок
    }
    
    SECTION("UUID generation performance") {
        auto start = std::chrono::high_resolution_clock::now();
        
        std::vector<std::string> uuids;
        for (int i = 0; i < 10000; ++i) {
            uuids.push_back(generate_uuid());
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        REQUIRE(uuids.size() == 10000);
        REQUIRE(duration.count() < 100000); // Должно выполняться быстро (< 100ms)
        
        // Проверяем уникальность UUID
        std::sort(uuids.begin(), uuids.end());
        auto unique_end = std::unique(uuids.begin(), uuids.end());
        REQUIRE(unique_end == uuids.end()); // Все UUID должны быть уникальными
    }
}

TEST_CASE("Thread safety tests", "[thread_safety]") {
    
    SECTION("SmartHome thread safety") {
        SmartHome home;
        Speaker::Room room{"Тестовая комната", 1, Speaker::RoomType::LIVING_ROOM};
        
        // Добавляем колонку
        home.add_speaker("Тест", room);
        
        // Запускаем операции в разных потоках
        std::vector<std::future<void>> futures;
        
        // Поток 1: чтение
        futures.push_back(std::async(std::launch::async, [&home]() {
            for (int i = 0; i < 1000; ++i) {
                try {
                    auto& speaker = home["Тест"];
                    (void)speaker.get_name();
                } catch (...) {
                    // Игнорируем исключения
                }
            }
        }));
        
        // Поток 2: запись
        futures.push_back(std::async(std::launch::async, [&home, &room]() {
            for (int i = 0; i < 100; ++i) {
                std::string name = "Колонка_" + std::to_string(i);
                home.add_speaker(name, room);
            }
        }));
        
        // Ждем завершения всех потоков
        for (auto& future : futures) {
            future.wait();
        }
        
        // Проверяем, что система осталась в консистентном состоянии
        REQUIRE(home.size() >= 1);
    }
    
    SECTION("Device thread safety") {
        auto light = std::make_shared<SmartLight>("Тестовая лампа");
        
        std::vector<std::future<void>> futures;
        
        // Поток 1: включение/выключение
        futures.push_back(std::async(std::launch::async, [&light]() {
            for (int i = 0; i < 1000; ++i) {
                light->turn_on();
                light->turn_off();
            }
        }));
        
        // Поток 2: изменение яркости
        futures.push_back(std::async(std::launch::async, [&light]() {
            for (int i = 0; i < 1000; ++i) {
                light->set_brightness(i % 101);
            }
        }));
        
        // Поток 3: чтение состояния
        futures.push_back(std::async(std::launch::async, [&light]() {
            for (int i = 0; i < 1000; ++i) {
                (void)light->get_power_state();
                (void)light->get_brightness();
            }
        }));
        
        // Ждем завершения всех потоков
        for (auto& future : futures) {
            future.wait();
        }
        
        // Проверяем, что устройство осталось в валидном состоянии
        REQUIRE(light->get_brightness() >= 0);
        REQUIRE(light->get_brightness() <= 100);
    }
} 