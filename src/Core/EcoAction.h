//
// Created by USER on 22/05/2025.
//

#ifndef ECOACTION_H
#define ECOACTION_H

#include <string>

class EcoAction {
private:
    std::string actionName;
    float co2Saved;

public:
    EcoAction(std::string name, float co2);
    int calculatePoints() const;
    std::string getDetails() const;
};

#endif // ECOACTION_H