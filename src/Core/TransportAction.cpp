#include "TransportAction.h"
#include <sstream>

TransportAction::TransportAction(std::string vehicle, float co2)
        : EcoAction("Transport", co2), vehicleType(std::move(vehicle)) {}

std::string TransportAction::getFullDetails() const {
    std::ostringstream details;
    details << getDetails()  // Inherited method
            << "\nVehicle: " << vehicleType;
    return details.str();
}