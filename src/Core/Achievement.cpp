
#include "Achievement.h"
#include <iostream>
#include "ActionLogger.h"


void AchievementSystem::checkAchievements(const ActionLogger& logger) {
    // First Action
    if(!achievements["First Step"] && logger.getTotalActions() >= 1) {
        achievements["First Step"] = true;
    }

    // 100kg CO₂ Saved
    if(!achievements["Carbon Saver"] && logger.getTotalCo2Saved() >= 100) {
        achievements["Carbon Saver"] = true;
    }
}

void AchievementSystem::displayAchievements() const {
    std::cout << "\n🏆 Earned Badges:\n";
    for(const auto& [name, unlocked] : achievements) {
        std::cout << " • " << (unlocked ? "✅ " : "🔒 ") << name << "\n";
    }
}

bool AchievementSystem::isUnlocked(const std::string& achievement) const {
    return achievements.at(achievement);
}