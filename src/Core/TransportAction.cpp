#include "TransportAction.h"
#include <sstream>

TransportAction::TransportAction(std::string vehicle, float co2)
        : EcoAction("Transport", co2), vehicleType(std::move(vehicle)) {}

std::string TransportAction::getDetails() const {
    std::ostringstream details;
    details << "Action: " << actionName
            << "\nCO₂ Saved: " << co2Saved << " kg"
            << "\nVehicle: " << vehicleType
            << "\nTime: " << getTimestamp();
    return details.str();
}