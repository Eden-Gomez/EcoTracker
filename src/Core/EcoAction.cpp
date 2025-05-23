#include "EcoAction.h"
#include <sstream>
#include <ctime>

EcoAction::EcoAction(std::string name, float co2)
        : actionName(std::move(name)), co2Saved(co2), timestamp(std::time(nullptr)) {}

int EcoAction::calculatePoints() const {
    return static_cast<int>(co2Saved * 2);
}

std::string EcoAction::getTimestamp() const {
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%b %d %Y, %H:%M", std::localtime(&timestamp));
    return buffer;
}
