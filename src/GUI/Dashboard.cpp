

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
        : user(profile), logger(actionLogger),
          dailyChallenge("Bike 10km", 10) {}  // Sample challenge

void Dashboard::printHeader() const {
    std::cout << COLOR_GREEN
              << "=== ECO HERO DASHBOARD ===\n"
              << COLOR_RESET;
}

void Dashboard::printProgressBar(float percentage) const {
    const int totalBars = 20;
    int bars = static_cast<int>(std::round(percentage * totalBars));

    if (percentage > 0.0f && bars == 0) {
        bars = 1;  // Ensure at least 1 bar if progress > 0
    }

    std::cout << "[";
    for (int i = 0; i < totalBars; i++) {
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
    const float progressPercentage = static_cast<float>(progressPoints) / 1000.0f;

    const auto& recentActions = logger.getRecentActions();

    // Daily challenge display
    std::cout << "\n=== Daily Challenge ===\n";
    std::cout << dailyChallenge.getStatus() << "\n";

    std::cout << "\n🌟 Level: " << level
              << "\nPoints: " << points
              << "\nTotal CO₂ Saved: " << logger.getTotalCo2Saved() << " kg\n";

    achievements.displayAchievements();

    std::cout << "\n=== Recent Actions ===\n";
    int count = 1;
    for (const auto& actionPtr : recentActions) {
        std::cout << count++ << ". " << actionPtr->getSummary() << "\n";
    }

    std::cout << "\nProgress to Next Level:\n";
    printProgressBar(progressPercentage);
}
