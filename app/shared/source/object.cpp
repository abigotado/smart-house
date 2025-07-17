#include "../include/object.h"

namespace smart_house {
std::ostream& operator<<(std::ostream& os, const Object& obj) {
    os << obj.to_string();
    return os;
}
} // namespace smart_house 