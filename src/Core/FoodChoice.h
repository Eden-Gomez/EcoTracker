#ifndef FOODCHOICE_H
#define FOODCHOICE_H

#include "EcoAction.h"
#include <ctime>

class FoodChoice : public EcoAction {
private:
    std::string mealType;
    bool isVegan;
    std::time_t mealDate;

public:
    FoodChoice(std::string mealType, bool vegan, float co2,
               std::time_t date = std::time(nullptr));
    std::time_t getDate() const { return mealDate; }
    std::string getDetails() const override;
    int calculatePoints() const override;

    // Add these getters
    std::string getMealType() const { return mealType; }
    bool isVeganMeal() const { return isVegan; }
};

#endif