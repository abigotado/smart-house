#pragma once

#include <string>

namespace smart_house {

/**
 * @brief Базовый абстрактный класс для всех объектов системы умного дома
 */
class Object {
    public:
        virtual ~Object() = default;
        
        /// Возвращает строковое представление объекта
        [[nodiscard]] virtual std::string to_string() const = 0;
        
    protected:
        // Защищенный конструктор - предотвращает создание экземпляров Object
        Object() = default;
};

std::ostream& operator<<(std::ostream& os, const Object& obj);

} 