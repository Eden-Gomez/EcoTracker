#include "EcoAction.h"
#include <sstream>

EcoAction::EcoAction(std::string name, float co2)
        : actionName(std::move(name)), co2Saved(co2) {}

int EcoAction::calculatePoints() const {
    return static_cast<int>(co2Saved * 2);  // 0.5 kg CO₂ = 1 point
}

std::string EcoAction::getDetails() const {
    std::ostringstream details;
    details << "Action: " << actionName
            << "\nCO₂ Saved: " << co2Saved << " kg"
            << "\nPoints Earned: " << calculatePoints();
    return details.str();
}