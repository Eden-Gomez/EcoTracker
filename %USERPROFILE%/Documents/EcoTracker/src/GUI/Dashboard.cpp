#include "../GUI/Dashboard.h"
#include <iostream>
#include "../Core/UserProfile.h"
#include "../Core/Achievement.h"
#include <iomanip>  // For setw()

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
    std::cout << "[";
    const int totalBars = 20;
    int filledBars = static_cast<int>(percentage * totalBars);

    // Ensure minimum 1 bar when there's progress
    if(percentage > 0 && filledBars == 0) filledBars = 1;

    for(int i=0; i<filledBars; i++) std::cout << "=";
    for(int i=filledBars; i<totalBars; i++) std::cout << " ";

    std::cout << "] " << static_cast<int>(percentage * 100) << "%\n";
}
void Dashboard::display() const {
    printHeader();

//    achievements.checkAchievements(logger);

    std::cout << "\n🌟 Level: " << user.getCarbonPoints()/1000 + 1
              << "\nPoints: " << user.getCarbonPoints()
              << "\nTotal CO₂ Saved: " << logger.getTotalCo2Saved() << " kg\n";

    achievements.displayAchievements();

    std::cout << "\n=== Recent Actions ===\n";
    logger.displayRecentActions();

    std::cout << "\nProgress to Next Level:\n";
    printProgressBar((user.getCarbonPoints() % 1000)/1000.0f);

}



