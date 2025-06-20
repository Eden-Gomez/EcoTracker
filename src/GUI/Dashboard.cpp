#include "../GUI/Dashboard.h"
#include <iostream>
#include "../Core/UserProfile.h"
#include "../Core/Achievement.h"
#include <iomanip>  // For setw()
#include <cmath>

// Color codes for terminal (ANSI escape codes)
#define COLOR_GREEN "\033[32m"
#define COLOR_RESET "\033[0m"


Dashboard::Dashboard(const UserProfile& profile, const ActionLogger& actionLogger)
        : user(profile), logger(actionLogger) {}
//void Dashboard::addAction(const std::string& action) {
//    recentActions.push_back(action);
//    if(recentActions.size() > 5) recentActions.erase(recentActions.begin());
//}

void Dashboard::printHeader() const {
    std::cout << COLOR_GREEN
              << "=== ECO HERO DASHBOARD ===\n"
              << COLOR_RESET;
}

void Dashboard::printProgressBar(float percentage) const {
    // Calculate the number of bars to show (minimum 1 if there's progress)
    std::cout << "[";
    const int totalBars = 20;
    int bars = static_cast<int>(std::round(percentage * totalBars));
    int filledBars = static_cast<int>(percentage * totalBars);

    // Ensure at least one bar is shown if there's any progress
    if (percentage > 0.0f && bars == 0) {
        bars = 1;
    }

    // Print the progress bar
    std::cout << "[";
    for(int i = 0; i < totalBars; i++) {
        if (i < bars) {
            std::cout << "=";
        } else {
            std::cout << " ";
        }
    }
    std::cout << "] " << static_cast<int>(percentage * 100) << "%\n";
}

void Dashboard::display() const {
    printHeader();

    achievements.checkAchievements(logger);

    // Calculate progress to next level
    const int points = user.getCarbonPoints();
    const int level = points / 1000 + 1;
    const int progressPoints = points % 1000;
    const float progressPercentage = progressPoints / 1000.0f;



    std::cout << "\n🌟 Level: " << user.getCarbonPoints()/1000 + 1
              << "\nPoints: " << user.getCarbonPoints()
              << "\nTotal CO₂ Saved: " << logger.getTotalCo2Saved() << " kg\n";
//This line is to display achievements, remember
    achievements.displayAchievements();

    // Display recent actions
    std::cout << "\n=== Recent Actions ===\n";
    logger.displayRecentActions();


    // Display progress bar
    std::cout << "\nProgress to Next Level:\n";
    printProgressBar((user.getCarbonPoints() % 1000)/1000.0f);




}


