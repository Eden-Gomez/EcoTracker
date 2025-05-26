#ifndef TRANSPORTACTION_H
#define TRANSPORTACTION_H

#include "EcoAction.h"
#include <string>

class TransportAction : public EcoAction {
private:
    std::string vehicleType;

public:
    TransportAction(std::string vehicle, float co2);
    std::string getDetails() const override;
    int calculatePoints() const override;

    // Add this getter
    std::string getVehicle() const { return vehicleType; }
};

#endif