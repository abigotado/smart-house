#pragma once

#include <string>

namespace smart_house {

/**
 * Базовый абстрактный класс для всех объектов системы умного дома
 * Предоставляет общий интерфейс для строкового представления
 */
class Object {
    public:
        virtual ~Object() = default;
        
        /**
         * Возвращает строковое представление объекта
         * @return строковое представление объекта
         */
        [[nodiscard]] virtual std::string to_string() const = 0;
        
    protected:
        // Защищенный конструктор по умолчанию - предотвращает создание экземпляров Object
        Object() = default;
};

} 