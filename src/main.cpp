#include "GUI/Dashboard.h"
#include <iostream>
#include <windows.h>  // For SetConsoleOutputCP

int main() {
    SetConsoleOutputCP(CP_UTF8);  // this line is to enable UTF-8 output
    try {
        UserProfile user("ClimateChampion");
        Dashboard dashboard(user);

        user.addPoints(150);  // Bike commute
        dashboard.addAction("🚲 Biked to school (50 pts)");

        user.addPoints(300);  // Vegan week
        dashboard.addAction("🌱 7 Vegan meals (300 pts)");

        dashboard.display();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}