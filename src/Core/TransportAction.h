#ifndef TRANSPORTACTION_H
#define TRANSPORTACTION_H

#include "EcoAction.h"

class TransportAction : public EcoAction {
private:
    std::string vehicleType;

public:
    TransportAction(std::string vehicle, float co2);
    std::string getFullDetails() const;
};

#endif // TRANSPORTACTION_H