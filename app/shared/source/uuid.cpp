#include "../include/uuid.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <array>

namespace smart_house {

std::string generate_uuid() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<uint32_t> dis(0, 0xFFFFFFFF);

    std::array<uint32_t, 4> data = { dis(gen), dis(gen), dis(gen), dis(gen) };

    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    ss << std::setw(8) << data[0] << "-";
    ss << std::setw(4) << ((data[1] >> 16) & 0xFFFF) << "-";
    ss << std::setw(4) << ((data[1] >> 0) & 0xFFFF) << "-";
    ss << std::setw(4) << ((data[2] >> 16) & 0xFFFF) << "-";
    ss << std::setw(4) << ((data[2] >> 0) & 0xFFFF);
    ss << std::setw(8) << data[3];
    return ss.str();
}

} // namespace smart_house 