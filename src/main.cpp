#include "GUI/Menu.h"
#include "Core/UserProfile.h"
#include "GUI/Dashboard.h"
#include <iostream>
#include <windows.h>  // For SetConsoleOutputCP





void mainMenuLoop(UserProfile& user, Dashboard& dashboard) {
    Menu mainMenu("Main Menu");
    mainMenu.addItem("View Dashboard");
    mainMenu.addItem("Log New Action");
    mainMenu.addItem("Save & Exit");

    while(true) {
        switch(mainMenu.display()) {
            case 1:  // View Dashboard
                dashboard.display();
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;

            case 2:  // Log Action
                // We'll implement this next
                std::cout << "Action logging coming soon!\n";
                break;

            case 3:  // Exit
                user.saveToFile("userdata.txt");
                return;
        }
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);  // Add this line to enable UTF-8 output
    try {
        UserProfile user("EcoWarrior");
        Dashboard dashboard(user);
        mainMenuLoop(user, dashboard);
    } catch (const std::exception& e) {
        std::cerr << "Fatal Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}