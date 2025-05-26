#include "TransportAction.h"
#include <sstream>

TransportAction::TransportAction(std::string vehicle, float co2)
        : EcoAction("Transport", co2), vehicleType(std::move(vehicle)) {}

int TransportAction::calculatePoints() const {
    return static_cast<int>(co2Saved * 2);  // 1kg CO₂ = 2 points
}

std::string TransportAction::getDetails() const {
    std::ostringstream details;
    details << "Action: " << actionName
            << "\nCO₂ Saved: " << co2Saved << " kg"
            << "\nVehicle: " << vehicleType
            << "\nTime: " << getTimestamp();
    return details.str();
}
