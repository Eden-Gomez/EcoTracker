#ifndef FOODCHOICE_H
#define FOODCHOICE_H

#include "EcoAction.h"

/**
 * Tracks environmental impact of dietary choices
 * Inherits from EcoAction base class
 */
class FoodChoice : public EcoAction {
private:
    std::string mealType;
    bool isVegan;

public:
    FoodChoice(std::string meal, bool vegan, float co2);
    std::string getDetails() const override;
};

#endif // FOODCHOICE_H