#include "../GUI/Dashboard.h"
#include <iostream>
#include "../Core/UserProfile.h"
#include "../Core/Achievement.h"
#include <iomanip>  // For setw()

// Color codes for terminal (ANSI escape codes)
#define COLOR_GREEN "\033[32m"
#define COLOR_RESET "\033[0m"

//Dashboard::Dashboard(const UserProfile& profile) : user(profile) {}
Dashboard::Dashboard(const UserProfile& profile, const ActionLogger& actionLogger)
        : user(profile), logger(actionLogger) {}
void Dashboard::addAction(const std::string& action) {
    recentActions.push_back(action);
    if(recentActions.size() > 5) recentActions.erase(recentActions.begin());
}

void Dashboard::printHeader() const {
    std::cout << COLOR_GREEN
              << "=== ECO HERO DASHBOARD ===\n"
              << COLOR_RESET;
}

void Dashboard::printProgressBar(float percentage) const {
    std::cout << "[";
    int bars = static_cast<int>(percentage * 20);
    for(int i=0; i<20; i++){
        std::cout << (i < bars ? "=" : " ");
    }
    std::cout << "] " << int(percentage * 100) << "%\n";
}

void Dashboard::display() const {
    printHeader();

    std::cout << "\n🌟 Level: " << user.getCarbonPoints()/1000 + 1
              << "\nPoints: " << user.getCarbonPoints()
              << "\nTotal CO₂ Saved: " << logger.getTotalCo2Saved() << " kg\n";

    logger.displayRecentActions();

    std::cout << "\nProgress to Next Level:\n";
    printProgressBar((user.getCarbonPoints() % 1000)/1000.0f);

    static AchievementSystem achievements;
    achievements.checkAchievements(logger);
    achievements.displayAchievements();
}



