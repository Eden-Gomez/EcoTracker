#ifndef TRANSPORTACTION_H
#define TRANSPORTACTION_H

#include "EcoAction.h"
#include <string>

/**
 * Specialized class for transportation-related eco actions
 * Inherits from EcoAction base class
 */
class TransportAction : public EcoAction {
private:
    std::string vehicleType;

public:
    TransportAction(std::string vehicle, float co2);
    std::string getDetails() const override;
};

#endif // TRANSPORTACTION_H