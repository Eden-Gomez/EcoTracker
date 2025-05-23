#include "GUI/Menu.h"
#include "Core/UserProfile.h"
#include "GUI/Dashboard.h"
#include "Core/TransportAction.h"
#include "Core/ActionLogger.h"
#include "Core/FoodChoice.h"
#include <iostream>
#include <windows.h>  // For SetConsoleOutputCP

float getValidatedInput(const std::string& prompt) {
    float input;
    std::cout << prompt;
    while (!(std::cin >> input)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input. Try again: ";
    }
    return input;
}


void logNewAction(ActionLogger& logger) {
    Menu typeMenu("Select Action Type");
    typeMenu.addItem("Transportation");
    typeMenu.addItem("Food Choice");

    switch(typeMenu.display()) {
        case 1: {
            std::string vehicle;
            float co2 = getValidatedInput("CO₂ saved (kg): ");
            std::cout << "Vehicle type: ";
            std::cin >> vehicle;
            logger.addAction(std::make_unique<TransportAction>(vehicle, co2));
            break;
        }
        case 2: {
            std::string meal;
            bool vegan;
            float co2 = getValidatedInput("CO₂ saved (kg): ");
            std::cout << "Meal description: ";
            std::cin.ignore();
            std::getline(std::cin, meal);
            std::cout << "Vegan? (1/0): ";
            std::cin >> vegan;
            logger.addAction(std::make_unique<FoodChoice>(meal, vegan, co2));
            break;
        }
    }
}



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

void logTransportAction(ActionLogger& logger) {
    std::string vehicle;
    std::cout << "Enter vehicle type: ";
    std::cin.ignore();
    std::getline(std::cin, vehicle);

    float co2;
    std::cout << "Enter CO₂ saved (kg): ";
    std::cin >> co2;

    logger.addAction(
            std::make_unique<TransportAction>(vehicle, co2)
    );
    std::cout << "Action logged successfully!\n";
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