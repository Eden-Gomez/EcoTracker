
#include "Achievement.h"
#include <iostream>
#include "ActionLogger.h"
#include "FoodChoice.h"
#include <vector>
#include <set>

void AchievementSystem::checkAchievements(const ActionLogger& logger) {
    // First Step
    achievements[0].current = logger.getTotalActions();

    // Carbon Saver
    achievements[1].current = static_cast<int>(logger.getTotalCo2Saved());


    // Vegan Week - Track consecutive calendar days
    std::set<std::time_t> veganDays;
    const auto& actions = logger.getActions();

    for(const auto& action : actions) {
        if(auto* food = dynamic_cast<FoodChoice*>(action.get())) {
            if(food->isVeganMeal()) {
                std::time_t dateValue = food->getDate();      // Store the return value
                std::tm* tm = std::localtime(&dateValue);     // Pass a pointer to that variable

                std::time_t date = std::mktime(new std::tm{
                        0, 0, 0, // hh, mm, ss
                        tm->tm_mday,
                        tm->tm_mon,
                        tm->tm_year
                });
                veganDays.insert(date);
            }
        }
    }

    achievements[2].current = veganDays.size();

    // Bike Master
    achievements[3].current = logger.getTransportActionCount();

    // Eco Hero
    achievements[4].current = logger.getTotalPoints();

    // Update unlocks
    for(auto& ach : achievements) {
        ach.unlocked = (ach.current >= ach.target);
    }
}

void AchievementSystem::displayAchievements() const {
    std::cout << "\n=== Achievements ===\n";
    for(const auto& ach : achievements) {
        std::cout << " • " << (ach.unlocked ? "✅ " : "🕒 ")
                  << ach.name << " (" << ach.current << "/" << ach.target << ")\n";
    }
}

bool AchievementSystem::isUnlocked(const std::string& name) const {
    for(const auto& ach : achievements) {
        if(ach.name == name) return ach.unlocked;
    }
    return false;
}