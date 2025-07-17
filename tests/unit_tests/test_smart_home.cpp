#include <catch2/catch_test_macros.hpp>
#include "../../app/home/include/smart_home.h"
#include "../../app/speaker/include/speaker.h"

using namespace smart_house;

TEST_CASE("SmartHome basic functionality", "[smart_home]") {
    SmartHome home;
    
    SECTION("Constructor and ID") {
        REQUIRE(!home.get_id().empty());
        REQUIRE(home.size() == 0);
    }
    
    SECTION("Adding speakers") {
        Speaker::Room living_room{"Гостиная", 1, Speaker::RoomType::LIVING_ROOM};
        Speaker::Room kitchen{"Кухня", 2, Speaker::RoomType::KITCHEN};
        
        REQUIRE(home.add_speaker("Алиса", living_room) == true);
        REQUIRE(home.add_speaker("Маруся", kitchen) == true);
        REQUIRE(home.size() == 2);
        
        // Попытка добавить колонку с тем же именем
        REQUIRE(home.add_speaker("Алиса", living_room) == false);
        REQUIRE(home.size() == 2);
    }
    
    SECTION("Accessing speakers by name") {
        Speaker::Room room{"Комната", 1, Speaker::RoomType::LIVING_ROOM};
        home.add_speaker("Тест", room);
        
        REQUIRE_NOTHROW(home["Тест"]);
        REQUIRE(home["Тест"].get_name() == "Тест");
        
        // Доступ к несуществующей колонке должен выбросить исключение
        REQUIRE_THROWS(home["Несуществующая"]);
    }
    
    SECTION("Moving speakers") {
        Speaker::Room room1{"Комната1", 1, Speaker::RoomType::LIVING_ROOM};
        Speaker::Room room2{"Комната2", 2, Speaker::RoomType::KITCHEN};
        
        home.add_speaker("Тест", room1);
        REQUIRE(home.move_speaker("Тест", room2) == true);
        REQUIRE(home["Тест"].get_room().room_type == Speaker::RoomType::KITCHEN);
        
        // Перемещение несуществующей колонки
        REQUIRE(home.move_speaker("Несуществующая", room1) == false);
    }
    
    SECTION("Renaming speakers") {
        Speaker::Room room{"Комната", 1, Speaker::RoomType::LIVING_ROOM};
        home.add_speaker("СтароеИмя", room);
        
        REQUIRE(home.rename_speaker("СтароеИмя", "НовоеИмя") == true);
        REQUIRE_NOTHROW(home["НовоеИмя"]);
        REQUIRE_THROWS(home["СтароеИмя"]);
        
        // Переименование в уже существующее имя
        home.add_speaker("Другое", room);
        REQUIRE(home.rename_speaker("НовоеИмя", "Другое") == false);
    }
    
    SECTION("Removing speakers") {
        Speaker::Room room{"Комната", 1, Speaker::RoomType::LIVING_ROOM};
        home.add_speaker("Тест", room);
        
        REQUIRE(home.remove_speaker("Тест") == true);
        REQUIRE(home.size() == 0);
        REQUIRE_THROWS(home["Тест"]);
        
        // Удаление несуществующей колонки
        REQUIRE(home.remove_speaker("Несуществующая") == false);
    }
    
    SECTION("Getting all speakers") {
        Speaker::Room room1{"Комната1", 1, Speaker::RoomType::LIVING_ROOM};
        Speaker::Room room2{"Комната2", 2, Speaker::RoomType::KITCHEN};
        
        home.add_speaker("Б", room1);
        home.add_speaker("А", room2);
        
        const auto& speakers = home.get_speakers();
        auto it = speakers.begin();
        REQUIRE(it->first == "А"); // Сортировка по имени
        ++it;
        REQUIRE(it->first == "Б");
    }
} 