#include "FoodChoice.h"
#include <sstream>
#include "DailyChallenge.h"

std::string FoodChoice::getSummary() const {
    std::ostringstream oss;
    oss << "[" << (isVegan ? "Vegan Meal" : "Meal") << "] Saved " << co2Saved
        << " kg CO₂ (+" << calculatePoints() << " points)";
    return oss.str();
}
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

void FoodChoice::applyEffects(UserProfile& user, DailyChallenge& challenge) {
    int points = calculatePoints();
    user.addPoints(points);

    // For example, if vegan meal, update challenge progress
    if (isVegan) {
        challenge.updateProgress(1);
    }


}