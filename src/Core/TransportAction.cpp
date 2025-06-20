#include "TransportAction.h"
#include "UserProfile.h"
#include "DailyChallenge.h"
#include <sstream>


std::string TransportAction::getSummary() const {
    std::ostringstream oss;
    oss << "[" << vehicleType << "] Saved " << co2Saved << " kg CO₂ (+"
        << calculatePoints() << " points)";
    return oss.str();
}
TransportAction::TransportAction(std::string vehicle, float co2)
        : EcoAction("Transport", co2), vehicleType(std::move(vehicle)) {}

int TransportAction::calculatePoints() const {
    return static_cast<int>(co2Saved * 2);  // 1kg CO₂ = 2 points
}

void TransportAction::applyEffects(UserProfile& user, DailyChallenge& challenge) {
    int points = calculatePoints();
    user.addPoints(points);

    // If bike trip, update challenge
    if(vehicleType.find("Bike") != std::string::npos) {
        challenge.updateProgress(1);  // Count each bike trip
    }
}

std::string TransportAction::getDetails() const {
    std::ostringstream details;
    details << "Action: " << actionName
            << "\nCO₂ Saved: " << co2Saved << " kg"
            << "\nVehicle: " << vehicleType
            << "\nTime: " << getTimestamp();
    return details.str();
}
