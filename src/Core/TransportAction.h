#ifndef TRANSPORTACTION_H
#define TRANSPORTACTION_H

#include "EcoAction.h"
#include <string>

// 🔧 Forward declarations
class UserProfile;
class DailyChallenge;

class TransportAction : public EcoAction {
private:
    std::string vehicleType;
    float co2Saved;
public:
    TransportAction(std::string vehicle, float co2);
    std::string getDetails() const override;
    int calculatePoints() const override;

    void applyEffects(UserProfile& user, DailyChallenge& challenge) override;

    std::string getVehicle() const { return vehicleType; }

    std::string getSummary() const override;
};

#endif