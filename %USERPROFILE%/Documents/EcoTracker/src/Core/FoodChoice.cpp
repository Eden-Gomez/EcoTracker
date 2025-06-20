#include "FoodChoice.h"
#include <sstream>

FoodChoice::FoodChoice(std::string mealType, bool vegan, float co2,
                       std::time_t date)
        : EcoAction("Food Choice", co2),
          mealType(std::move(mealType)),
          isVegan(vegan),
          mealDate(date) {}

          //Add this implementation
int FoodChoice::calculatePoints() const {
    return static_cast<int>(co2Saved * 2); // Same as TransportAction
}

//Existing getDetails()
std::string FoodChoice::getDetails() const {
    std::ostringstream details;
    details << "Action: " << actionName
            << "\nMeal: " << mealType
            << "\nVegan: " << (isVegan ? "Yes" : "No")
            << "\nCO₂ Saved: " << co2Saved << " kg"
            << "\nTime: " << getTimestamp();
    return details.str();
}