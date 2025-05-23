#include "FoodChoice.h"
#include <sstream>

FoodChoice::FoodChoice(std::string meal, bool vegan, float co2)
        : EcoAction("Food Choice", co2),
          mealType(std::move(meal)),
          isVegan(vegan) {}

std::string FoodChoice::getDetails() const {
    std::ostringstream details;
    details << "Action: " << actionName
            << "\nMeal: " << mealType
            << "\nVegan: " << (isVegan ? "Yes" : "No")
            << "\nCO₂ Saved: " << co2Saved << " kg"
            << "\nTime: " << getTimestamp();
    return details.str();
}